#pragma once

#include <vector>
#include <list>
#include <cstring>
#include <queue>
#include <stack>
#include <map>
#include <iterator>


using namespace std;


struct graph_node
{
	int num; //номер - это первый и последний индекс элемента матрицы
	int weight;
};


void add_node(list<graph_node> &nodes, int n);
void choose_point_to_go(const vector<string> &m, int size_r, int size_c, int i, int j, int& go, list<list<graph_node>> &g, int kirk);
int get_num(pair<int, int> p, int size_c);
char* calc_dir(int from, int to, int size_c);
bool is_way_element(char c);
void add_neighbours(const vector<string> &m, int size_r, int size_c, pair<int, int> cr, list<graph_node> &nodes);
void add(const vector<string> &m, int size_r, int size_c, int i, int j, list<list<graph_node>> &g);
stack<int> find_way(list<list<graph_node>> &g, int start, int finish);
