#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <iterator>

#define UP (-30)
#define DOWN (30)
#define RIGHT (1)
#define LEFT (-1)

using namespace std;

struct graph_node
{
	int num; //номер - это первый и последний индекс элемента матрицы
	int weight;
};

void add_node(list<graph_node> &nodes, int n);
void choose_point_to_go(vector<string> m, int size_r, int size_c, int i, int j, int& go, list<list<graph_node>> &g, int kirk);
int get_num(pair<int, int> p, int size_c);
char* calc_dir(int from, int to);
bool is_way_element(char c);
void add_neighbours(vector<string> map, int size_r, int size_c, pair<int, int> cr, list<graph_node> &nodes);
void add(vector<string> m, int size_r, int size_c, int i, int j, list<list<graph_node>> &g);
stack<int> find_way(list<list<graph_node>> &g, int start, int finish);


int main()
{
	int number_of_rows; // number of rows.
	int  number_of_colomns; // number of columns.
	int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
	cin >> number_of_rows >> number_of_colomns >> A; cin.ignore();

	list<list<graph_node>> graph; //граф
	pair<int, int> room_coordinate;
	pair<int, int> init_coordinate;

	bool room_found = false;
	bool go_back = false;

	// game loop
	while (1) {
		vector<string> _map(30); //карта 
		int go_to = 0;

		int kirk_r; // row where Kirk is located.
		int kirk_c; // column where Kirk is located.
		cin >> kirk_r >> kirk_c; cin.ignore();

		//положение кирка
		int kirk_pos = get_num({ kirk_r, kirk_c }, number_of_colomns);
		for (int i = 0; i < number_of_rows; i++)
		{
			string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
			cin >> ROW; cin.ignore();
			_map[i] = ROW;
		}

		if (kirk_r == room_coordinate.first
			&& kirk_c == room_coordinate.second)
			go_back = true;

		//graph init
		for (int i = 0; i < number_of_rows; i++)
		{
			for (int j = 0; j < number_of_colomns; j++)
			{
				if (_map[i][j] != '#'
					&& _map[i][j] != '?')
				{

					if (_map[i][j] == 'C')
					{
						//room
						room_found = true;
						room_coordinate.first = i;
						room_coordinate.second = j;
					}

					//init pos
					if (_map[i][j] == 'T')
					{
						init_coordinate.first = i;
						init_coordinate.second = j;
					}
					add(_map, number_of_rows, number_of_colomns, i, j, graph);


				}
			}
		}

		for (int i = 0; i < number_of_rows; i++) //определение точки, к которой нужно двигаться
		{
			for (int j = 0; j < number_of_colomns; j++)
			{
				choose_point_to_go(_map, number_of_rows, number_of_colomns, i, j, go_to, graph, kirk_pos);
				if (go_to)
				{
					break;
				}
			}
		}

		if (go_back)
		{
			go_to = get_num(init_coordinate, number_of_colomns);
			int go_from = get_num({ kirk_r, kirk_c }, number_of_colomns);
			stack<int> st = find_way(graph, go_from, go_to);
			char *c = calc_dir(go_from, st.top());
			cout << c;
		}
		else if (room_found && go_to == 0)
		{
			go_to = get_num(room_coordinate, number_of_colomns);
			int go_from = get_num({ kirk_r, kirk_c }, number_of_colomns);
			stack<int> st = find_way(graph, go_from, go_to);
			char *c = calc_dir(go_from, st.top());
			cout << c;
		}
		else
		{
			int go_from = get_num({ kirk_r, kirk_c }, number_of_colomns);
			stack<int> st = find_way(graph, go_from, go_to);
			char *c = calc_dir(go_from, st.top());
			cout << c;
		}
		cout << endl;
		graph.clear();
	}
}



void add(vector<string> m, int size_r, int size_c, int i, int j, list<list<graph_node>> &g)
{
	list<graph_node> temp_node;
	int temp_num = get_num({ i, j }, size_c);

	add_node(temp_node, temp_num);
	add_neighbours(m, size_r, size_c, { i, j }, temp_node);
	g.push_back(temp_node);
}


void choose_point_to_go(vector<string> m, int size_r, int size_c, int i, int j, int& go, list<list<graph_node>> &g, int kirk)
{
	int temp_num;
	temp_num = get_num({ i, j }, size_c);
	if ((i != 0 && m[i - 1][j] == '?')
		|| (j != 0 && m[i][j - 1] == '?')
		|| (j != size_c && m[i][j + 1] == '?')
		|| (i != size_r && m[i + 1][j] == '?'))
	{
		stack<int> st;
		int go_from = kirk;
		st = find_way(g, go_from, temp_num);
		if (st.size() != 0)
		{
			go = temp_num;
		}
	}
}

void add_node(list<graph_node> &nodes, int n)
{
	graph_node temp_elem;
	temp_elem.num = n;
	nodes.push_back(temp_elem);
}


//анализ соседей  
void add_neighbours(vector<string> map, int size_r, int size_c, pair<int, int> cr, list<graph_node> &nodes)
{
	if (cr.first != 0)
	{
		//UP
		if (is_way_element(map[cr.first - 1][cr.second]))
		{
			pair<int, int> temp_cr(cr.first - 1, cr.second);
			int temp_num = get_num(temp_cr, size_c);
			add_node(nodes, temp_num);
		}
	}
	if (cr.second != 0)
	{
		//LEFT
		if (is_way_element(map[cr.first][cr.second - 1]))
		{
			pair<int, int> temp_cr(cr.first, cr.second - 1);
			int temp_num = get_num(temp_cr, size_c);
			add_node(nodes, temp_num);
		}
	}
	if (cr.second < size_c - 1)
	{
		//RIGHT
		if (is_way_element(map[cr.first][cr.second + 1]))
		{
			pair<int, int> temp_cr(cr.first, cr.second + 1);
			int temp_num = get_num(temp_cr, size_c);
			add_node(nodes, temp_num);
		}
	}
	if (cr.first < size_r - 1)
	{
		//DOWN
		if (is_way_element(map[cr.first + 1][cr.second]))
		{
			pair<int, int> temp_cr(cr.first + 1, cr.second);
			int temp_num = get_num(temp_cr, size_c);
			add_node(nodes, temp_num);
		}
	}
}



stack<int> find_way(list<list<graph_node>> &g, int start, int finish)
{
	stack<int> way;

	int temp_weight = 0;
	int current_num = start;

	map <int, int> num_weight = { { current_num, temp_weight } };

	int counter = 0;
	int exp = 1;
	queue<int> for_counter; //очередь для присвоения номера-веса
	queue<int> que; //очередь на проверку 

	list<list<graph_node>> ::iterator it_g = g.begin();
	(*(*it_g).begin()).weight = temp_weight;
	temp_weight++;
	do
	{
		int temp_num = (*(*it_g).begin()).num;
		if (current_num == temp_num)
		{
			exp--;
			for (list<graph_node> ::iterator it_n = (*it_g).begin(); it_n != (*it_g).end(); it_n++)
			{
				map <int, int> ::iterator it;
				it = num_weight.find((*it_n).num);

				if (it == (num_weight.end()))
				{
					//заносим в map
					num_weight.insert(make_pair((*it_n).num, temp_weight));
					(*it_n).weight = temp_weight;
					que.push((*it_n).num);
					counter++;
				}
				else
					(*it_n).weight = it->second;
			}

			if (counter)
				for_counter.push(counter);

			if (exp == 0 && !que.empty())
			{
				exp = for_counter.front();
				for_counter.pop();
				temp_weight++;
			}

			//если очередь пуста - обход графа закончен
			if (que.empty())
			{
				map <int, int> ::iterator it;
				it = num_weight.find(finish);
				if (it == (num_weight.end()))
				{
					return way;
				}
				break;
			}

			//если не пуста - берем соседа из очереди
			current_num = que.front();
			que.pop();

			//сброс счетчика
			counter = 0;

			//сброс итератора
			it_g = g.begin();
		}
		else
		{
			//если не нашли, то идем дальше 
			++it_g;
		}
	} while (it_g != g.end());

	current_num = finish;
	way.push(finish);
	it_g = g.begin();
	do
	{
		int temp_num = (*(*it_g).begin()).num;
		if (current_num == temp_num)
		{
			list<graph_node> ::iterator it_n = (*it_g).begin();
			int min = (*it_n).weight;
			it_n++;
			int temp;
			for (it_n; it_n != (*it_g).end(); it_n++)
			{
				if ((*it_n).weight < min)
				{
					min = (*it_n).weight;
					temp = (*it_n).num;
				}
			}
			way.push(temp);

			if (min == 0)
			{
				way.pop();
				return way;
			}
			it_g = g.begin();
			current_num = temp;
		}

		else
		{
			//если не нашли, то идем дальше 
			++it_g;
		}
	} while (it_g != g.end());
}



char* calc_dir(int from, int to)
{
	if (from + UP == to)
		return "UP";
	else if (from + DOWN == to)
		return "DOWN";
	else if (from + RIGHT == to)
		return "RIGHT";
	else if (from + LEFT == to)
		return "LEFT";
	else
		return "error";
}

bool is_way_element(char c)
{
	if (c == '.'
		|| c == 'C'
		|| c == 'T')
	{
		return true;
	}
	else
	{
		return false;
	}
}


int get_num(pair<int, int> p, int size_c)
{
	return (p.first * size_c + p.second + 1);
}