/*
 * Source:
 * https://www.geeksforgeeks.org/graph-and-its-representations/
 * https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
 * https://medium.com/@vinay.vashist2003/graphs-data-structure-in-c-ab7b4205f41a
 * https://www.section.io/engineering-education/graphs-in-data-structure-using-cplusplus/
 *
 * https://www.geeksforgeeks.org/introduction-to-dijkstras-shortest-path-algorithm/?ref=lbp
 * https://favtutor.com/blogs/dijkstras-algorithm-cpp
 * https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
 *
 * https://www.geeksforgeeks.org/a-search-algorithm/
 * https://www.redblobgames.com/pathfinding/a-star/implementation.html#cpp
 * https://en.cppreference.com/w/cpp/language/operators | https://www.freecodecamp.org/news/how-to-overload-operators-in-cplusplus/
 * https://github.com/daancode/a-star/blob/master/source/AStar.cpp
 */

#pragma once
#include <unordered_map>
#include <vector>

using namespace std;

class Vertex
{
public:
	int VertexID;
	int Weight;

	Vertex(int VertexID, int Weight);
};

class AStarVertex
{
public:
	int VertexID;
	int GoCost; // Cost from start to current node 
	int HeuristicCost; // Heuristic cost from current node to end node
	int FinalCost; // Total cost of (gCost + hCost) At each step it picks the node/cell having the lowest ‘f’, and process that node/cell.

	AStarVertex(int VertexID, int GoCost, int HeuristicCost);

	bool operator > (const AStarVertex& OtherVertex) const
	{
		return FinalCost > OtherVertex.FinalCost;
	}

};

class Graph
{
public:
	Graph() = default;

	unordered_map<int, vector<Vertex>> AdjacencyList;
	unordered_map<int, vector<AStarVertex>> AdjacencyListAStar;
	unordered_map<int, vector<pair<int, int>>> AdjacencyListAStarTwo; // Node -> (Neighbour, Weight) pairs

	vector<int> BreadthFirstSearch(int StartVertex, int EndVertex);

	vector<int> DijsktraPathfinding(int StartVertex, int EndVertex);

	vector<int> AStarPathfinding(int StartVertex, int EndVertex);

	vector<int> AStarPathfindingTwo(int StartVertex, int EndVertex);

	int HeuristicCalculation(int StartVertex, int EndVertex);

	Vertex* CreateVertex(int VertexID, int Weight);

	void CreateEdge(int From, int To, int Weight);

	void CreateEdgeAStar(int From, int To, int Weight);

	void CreateGraph();

	void CreateAStarGraph();

	void PrintGraph();
};
