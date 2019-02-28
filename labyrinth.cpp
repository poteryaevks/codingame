
#include "functions.h"


#define TEST_MODE

#ifdef TEST_MODE

#include <gtest/gtest.h>
#include <conio.h>
#include "gtest.h"

#endif // TEST


int main(int argc, char* argv[])
{
#ifdef TEST_MODE

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	_getch();
	return 0;
#else

	int number_of_rows;
	int  number_of_columns;
	int  A;
	cin >> number_of_rows >> number_of_columns >> A; cin.ignore();

	list<list<graph_node>> graph;
	pair<int, int> room_coordinate;
	pair<int, int> init_coordinate;

	bool room_found = false;
	bool go_back = false;

	// game loop
	while (1)
	{
		vector<string> _map(number_of_rows + 1);
		int go_to = 0;

		int kirk_r; // row where Kirk is located.
		int kirk_c; // column where Kirk is located.
		cin >> kirk_r >> kirk_c; cin.ignore();

		//положение кирка
		int kirk_pos = get_num({ kirk_r, kirk_c }, number_of_columns);
		for (int i = 0; i < number_of_rows; i++)
		{
			cin >> _map[i]; cin.ignore();
		}

		if (kirk_r == room_coordinate.first
			&& kirk_c == room_coordinate.second)
			go_back = true;

		//graph init
		for (int i = 0; i < number_of_rows; i++)
		{
			for (int j = 0; j < number_of_columns; j++)
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
					add(_map, number_of_rows, number_of_columns, i, j, graph);
				}
			}
		}

		for (int i = 0; i < number_of_rows; i++) //определение точки, к которой нужно двигаться
		{
			for (int j = 0; j < number_of_columns; j++)
			{
				choose_point_to_go(_map, number_of_rows, number_of_columns, i, j, go_to, graph, kirk_pos);
				if (go_to)
				{
					break;
				}
			}
		}
		if (go_back)
		{
			go_to = get_num(init_coordinate, number_of_columns);
			int go_from = get_num({ kirk_r, kirk_c }, number_of_columns);
			stack<int> st = find_way(graph, go_from, go_to);
			char *c = calc_dir(go_from, st.top(), number_of_columns);
			cout << c;
		}
		else if (room_found && go_to == 0)
		{
			go_to = get_num(room_coordinate, number_of_columns);
			int go_from = get_num({ kirk_r, kirk_c }, number_of_columns);
			stack<int> st = find_way(graph, go_from, go_to);
			char *c = calc_dir(go_from, st.top(), number_of_columns);
			cout << c;
		}
		else
		{
			int go_from = get_num({ kirk_r, kirk_c }, number_of_columns);
			stack<int> st = find_way(graph, go_from, go_to);
			char *c = calc_dir(go_from, st.top(), number_of_columns);
			cout << c;
		}
		cout << endl;
		graph.clear();
	}

	return 1;

#endif // TEST
}