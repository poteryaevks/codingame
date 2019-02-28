#pragma once


#define MAP_1
#define MAP_2
#define MAP_3
#define MAP_4

#include "maps.h"

#define SET_NUMBER(x, y) x ## _ ## y
#define X_SET_NUMBER( x, y ) SET_NUMBER( x, y )


TEST(codingame_test, find_way)
{
	vector<map_point_collection> points;

#ifdef MAP_1
	points.push_back({
		X_SET_NUMBER(isolated_points, MAP_1_ID),
		X_SET_NUMBER(not_isolated_points, MAP_1_ID),
		X_SET_NUMBER(no_way, MAP_1_ID),
		X_SET_NUMBER(map, MAP_1_ID) });
#endif // MAP_1

#ifdef MAP_2
	points.push_back({
		X_SET_NUMBER(isolated_points, MAP_2_ID),
		X_SET_NUMBER(not_isolated_points, MAP_2_ID),
		X_SET_NUMBER(no_way, MAP_2_ID),
		X_SET_NUMBER(map, MAP_2_ID) });
#endif // MAP_2

#ifdef MAP_3
	points.push_back({
		X_SET_NUMBER(isolated_points, MAP_3_ID),
		X_SET_NUMBER(not_isolated_points, MAP_3_ID),
		X_SET_NUMBER(no_way, MAP_3_ID),
		X_SET_NUMBER(map, MAP_3_ID) });

#endif // MAP_3

#ifdef MAP_4
	points.push_back({
		X_SET_NUMBER(isolated_points, MAP_4_ID),
		X_SET_NUMBER(not_isolated_points, MAP_4_ID),
		X_SET_NUMBER(no_way, MAP_4_ID),
		X_SET_NUMBER(map, MAP_4_ID) });
#endif // MAP_4

	int start;
	list<list<graph_node>> graph;

	for each (auto el in points)
	{
		for (int j = 0; j < el.map.size(); j++)
		{
			int i = 0;
			while (el.map[j][i])
			{
				if (el.map[j][i] != '#'
					&& el.map[j][i] != '?')
				{
					if (el.map[j][i] == 'T')
					{
						start = get_num({ j, i }, el.map[j].size());
					}
					add(el.map, el.map.size(), el.map[j].size(), j, i, graph);
				}
				else
				{
					int temp = get_num({ j, i }, el.map[j].size());
					el.no_way.push_back(temp);
				}
				i++;
			}
		}

		for (size_t i = 0; i < el.no_way.size(); i++)
		{
			stack<int>  way = find_way(graph, start, el.no_way[i]);
			EXPECT_EQ(0, way.size());
		}

		for (size_t i = 0; i < el.isolated_points.size(); i++)
		{
			stack<int>  way = find_way(graph, start, el.isolated_points[i]);
			EXPECT_EQ(0, way.size());
		}

		for (size_t i = 0; i < el.not_isolated_points.size(); i++)
		{
			stack<int>  way = find_way(graph, start, el.not_isolated_points[i]);
			EXPECT_NE(0, way.size());
		}
		graph.clear();
	}
}