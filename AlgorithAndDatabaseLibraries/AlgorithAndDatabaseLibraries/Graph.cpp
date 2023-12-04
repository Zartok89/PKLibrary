#include "Graph.h"

#include <iostream>
#include <queue>

Vertex::Vertex(int VertexID, int Weight)
{
	this->VertexID = VertexID;
	this->Weight = Weight;
}

AStarVertex::AStarVertex(int VertexID, int GoCost, int HeuristicCost)
{
	this->VertexID = VertexID;
	this->GoCost = GoCost;
	this->HeuristicCost = HeuristicCost;
	this->FinalCost = GoCost + HeuristicCost;
}

vector<int> Graph::BreadthFirstSearch(int StartVertex, int EndVertex)
{
	queue<int> Queue;
	vector<bool> Visited(AdjacencyList.size(), false);
	vector<int> VertexParent(AdjacencyList.size(), -1);

	Queue.push(StartVertex);
	Visited[StartVertex] = true;

	while (!Queue.empty())
	{
		int CurrentVertex = Queue.front();
		Queue.pop();

		for (Vertex& node : AdjacencyList[CurrentVertex])
		{
			if (!Visited[node.VertexID])
			{
				Queue.push(node.VertexID);
				Visited[node.VertexID] = true;
				VertexParent[node.VertexID] = CurrentVertex;
			}
		}
	}

	vector<int> VertexPath;
	for (int i = EndVertex; i != -1; i = VertexParent[i])
	{
		VertexPath.push_back(i);
	}

	reverse(VertexPath.begin(), VertexPath.end());

	return VertexPath;
}

vector<int> Graph::DijsktraPathfinding(int StartVertex, int EndVertex)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PriorityQueue;
	vector<int> Distance(AdjacencyList.size(), numeric_limits<int>::max());
	vector<int> VertexParent(AdjacencyList.size(), -1);

	PriorityQueue.emplace(0, StartVertex);
	Distance[StartVertex] = 0;

	while (!PriorityQueue.empty())
	{
		int CurrentVertex = PriorityQueue.top().second;
		int CurrentDistance = PriorityQueue.top().first;
		PriorityQueue.pop();

		if (CurrentDistance > Distance[CurrentVertex])
		{
			continue;
		}

		for (Vertex& NeighborVertex : AdjacencyList[CurrentVertex])
		{
			int NewDistance = CurrentDistance + NeighborVertex.Weight;
			if (NewDistance < Distance[NeighborVertex.VertexID])
			{
				Distance[NeighborVertex.VertexID] = NewDistance;
				VertexParent[NeighborVertex.VertexID] = CurrentVertex;
				PriorityQueue.emplace(NewDistance, NeighborVertex.VertexID);
			}
		}
	}

	vector<int> VertexPath;
	for (int i = EndVertex; i != -1; i = VertexParent[i])
	{
		VertexPath.push_back(i);
	}

	reverse(VertexPath.begin(), VertexPath.end());
	return VertexPath;
}

vector<int> Graph::AStarPathfinding(int StartVertex, int EndVertex)
{
	priority_queue<AStarVertex, vector<AStarVertex>, greater<AStarVertex>> PriorityQueue;
	vector<int> GoCost(AdjacencyListAStar.size(), numeric_limits<int>::max());
	vector<int> VertexParent(AdjacencyListAStar.size(), -1);
	int HeuristicCost = HeuristicCalculation(StartVertex, EndVertex);

	PriorityQueue.emplace(StartVertex, 0, HeuristicCost);
	GoCost[StartVertex] = 0;

	while (!PriorityQueue.empty())
	{
		int CurrentVertex = PriorityQueue.top().VertexID;
		int CurrentGoCost = PriorityQueue.top().GoCost;
		PriorityQueue.pop();

		if (CurrentVertex == EndVertex)
		{
			break; // Found the destination
		}

		for (AStarVertex& NeighborVertex : AdjacencyListAStar[CurrentVertex])
		{
			int NewGoCost = CurrentGoCost + NeighborVertex.GoCost;
			if (NewGoCost < GoCost[NeighborVertex.VertexID])
			{
				GoCost[NeighborVertex.VertexID] = NewGoCost;
				VertexParent[NeighborVertex.VertexID] = CurrentVertex;

				int NewHeuristicCost = HeuristicCalculation(NeighborVertex.VertexID, EndVertex);
				PriorityQueue.emplace(NeighborVertex.VertexID, NewGoCost, NewHeuristicCost);
			}
		}
	}

	// Reconstruct the path
	vector<int> VertexPath;
	for (int i = EndVertex; i != -1; i = VertexParent[i])
	{
		VertexPath.push_back(i);
	}

	reverse(VertexPath.begin(), VertexPath.end());
	return VertexPath;
}

vector<int> Graph::AStarPathfindingTwo(int StartVertex, int EndVertex)
{
	// Priority	queue to store (f-score, node) pairs
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PriorityQueue;

	// Data structures for A* algorithm
	unordered_map<int, int> VertexParent; // Parent node of each node in the shortest path
	unordered_map<int, int> GoScore; // Cost from start node to each node
	unordered_map<int, int> FinalScore; // Estimated total cost from start node to end node passing through the current node

	// Initialization
	for (const auto& pair : AdjacencyListAStarTwo) 
	{
		int node = pair.first;
		GoScore[node] = numeric_limits<int>::max();
		FinalScore[node] = numeric_limits<int>::max();
	}
	
	GoScore[StartVertex] = 0;
	FinalScore[StartVertex] = HeuristicCalculation(StartVertex, EndVertex);

	PriorityQueue.emplace(FinalScore[StartVertex], StartVertex);

	// A* algorithm
	while (!PriorityQueue.empty()) 
	{
		int CurrentVertex = PriorityQueue.top().second;
		PriorityQueue.pop();

		if (CurrentVertex == EndVertex) 
		{
			// Reconstruct and return the path
			vector<int> VertexPath;
			while (VertexParent.find(CurrentVertex) != VertexParent.end()) 
			{
				VertexPath.insert(VertexPath.begin(), CurrentVertex);
				CurrentVertex = VertexParent[CurrentVertex];
			}
			VertexPath.insert(VertexPath.begin(), StartVertex);
			return VertexPath;
		}

		for (const auto& Neighbor : AdjacencyListAStarTwo[CurrentVertex]) 
		{
			int NeighborVertex = Neighbor.first;
			int NewGoScore = GoScore[CurrentVertex] + Neighbor.second;
			if (NewGoScore < GoScore[NeighborVertex]) 
			{
				VertexParent[NeighborVertex] = CurrentVertex;
				GoScore[NeighborVertex] = NewGoScore;
				FinalScore[NeighborVertex] = GoScore[NeighborVertex] + HeuristicCalculation(NeighborVertex, EndVertex);
				PriorityQueue.push({ FinalScore[NeighborVertex], NeighborVertex });
			}
		}
	}

	// If no path found, return an empty vector
	return vector<int>();
}

int Graph::HeuristicCalculation(int StartVertex, int EndVertex)
{
	// Calculate Euclidean distance as heuristic
	// For simplicity, let's assume nodes are one-dimensional and use absolute difference as heuristic
	return abs(StartVertex - EndVertex);
}

Vertex* Graph::CreateVertex(int VertexID, int Weight)
{
	return new Vertex(VertexID, Weight);
}

void Graph::CreateGraph()
{
	Vertex* Vertex0 = CreateVertex(0, 4);
	Vertex* Vertex1 = CreateVertex(1, 6);
	Vertex* Vertex2 = CreateVertex(2, 2);
	Vertex* Vertex3 = CreateVertex(3, 3);
	Vertex* Vertex4 = CreateVertex(4, 10);
	Vertex* Vertex5 = CreateVertex(5, 55);
	Vertex* Vertex6 = CreateVertex(6, 3);

	CreateEdge(0, 1, 4);
	CreateEdge(1, 2, 4);
	CreateEdge(2, 3, 2);
	CreateEdge(3, 4, 1);
	CreateEdge(4, 2, 7);
	CreateEdge(4, 5, 9);
	CreateEdge(4, 6, 15);
	CreateEdge(5, 6, 18);
	CreateEdge(6, 1, 22);
}

void Graph::CreateAStarGraph()
{
	CreateEdgeAStar(1, 2, 6); // S to A
	CreateEdgeAStar(1, 3, 5); // S to B
	CreateEdgeAStar(1, 4, 10); // S to C
	CreateEdgeAStar(2, 6, 6); // A to E
	CreateEdgeAStar(3, 6, 6); // B to E
	CreateEdgeAStar(3, 5, 7); // B to D
	CreateEdgeAStar(4, 5, 6); // C to D
	CreateEdgeAStar(5, 7, 6); // D to F
	CreateEdgeAStar(6, 7, 4); // E to F
	CreateEdgeAStar(7, 8, 3); // F to G
}

void Graph::CreateEdge(int From, int To, int Weight)
{
	AdjacencyList[From].emplace_back(To, Weight);
	AdjacencyList[To].emplace_back(From, Weight);
}

void Graph::CreateEdgeAStar(int From, int To, int Weight)
{
	AdjacencyListAStarTwo[From].emplace_back(To, Weight);
}

void Graph::PrintGraph()
{
	for (const pair<int, vector<Vertex>>& entry : AdjacencyList)
	{
		cout << "Vertex " << entry.first << " goes to -> |";

		for (const Vertex& node : entry.second)
		{
			cout << "Vertex " << node.VertexID << " (Weight: " << node.Weight << ") | ";
		}

		cout << std::endl;
	}
}