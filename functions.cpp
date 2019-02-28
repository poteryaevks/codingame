#include "functions.h"



void add(const vector<string> &m, int size_r, int size_c, int i, int j, list<list<graph_node>> &g)
{
	list<graph_node> temp_node;
	int temp_num = get_num({ i, j }, size_c);
	add_node(temp_node, temp_num);
	add_neighbours(m, size_r, size_c, { i, j }, temp_node);
	g.push_back(temp_node);
}


void choose_point_to_go(const vector<string> &m, int size_r, int size_c, int i, int j, int& go, list<list<graph_node>> &g, int kirk)
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
void add_neighbours(const vector<string> &m, int size_r, int size_c, pair<int, int> cr, list<graph_node> &nodes)
{
	if (cr.first != 0)
	{
		//UP
		if (is_way_element(m[cr.first - 1][cr.second]))
		{
			pair<int, int> temp_cr(cr.first - 1, cr.second);
			int temp_num = get_num(temp_cr, size_c);
			add_node(nodes, temp_num);
		}
	}
	if (cr.second != 0)
	{
		//LEFT
		if (is_way_element(m[cr.first][cr.second - 1]))
		{
			pair<int, int> temp_cr(cr.first, cr.second - 1);
			int temp_num = get_num(temp_cr, size_c);
			add_node(nodes, temp_num);
		}
	}
	if (cr.second < size_c - 1)
	{
		//RIGHT
		if (is_way_element(m[cr.first][cr.second + 1]))
		{
			pair<int, int> temp_cr(cr.first, cr.second + 1);
			int temp_num = get_num(temp_cr, size_c);
			add_node(nodes, temp_num);
		}
	}
	if (cr.first < size_r - 1)
	{
		//DOWN
		if (is_way_element(m[cr.first + 1][cr.second]))
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
					return way; //маршрут не найден
				}
				else
				{
					//восстанавливаем путь
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

	//если не нашли  - выход 
	return way;
}



char* calc_dir(int from, int to, int size_c)
{
	if (from - size_c == to)
		return "UP";
	else if (from + size_c == to)
		return "DOWN";
	else if (from + 1 == to)
		return "RIGHT";
	else if (from - 1 == to)
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
