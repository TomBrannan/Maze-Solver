#include "graph.h"

// Adds a vertex to the graph and assign it the next available id
void graph::addVertex()
{
	vertex vert;
	vert.id = vertices.size();
	vertices.push_back(vert);
}

// Adds an undirected edge between vertices with the given ids
void graph::addEdge(int id1, int id2)
{
	vertices[id1].neighbors.push_back(&vertices[id2]);
	//The inverse will be found later when looking at vertices[id2]
}

// Conducts a breadth-first search from the vertex with the specified id
void graph::breadthFirst(int start)
{
	vertex* s = &vertices[start];
	queue<vertex> q;

	//Initialize each vertex's distance to (essentially) infinity, and path pointer to null.
	for (vector<vertex>::iterator iter = vertices.begin(); iter != vertices.end(); ++iter)
	{
		(*iter).distance = 2147000000;
		(*iter).path = NULL;
	}

	s->distance = 0; //Set the starting vertex's distance to 0
	q.push(*s);		 //And push it onto the stack

	while (!q.empty())
	{
		vertex v = q.front();
		q.pop();

		//Visit each of this vertex's neighbors to set distance and path info
		for (list<vertex*>::iterator iterAdj = v.neighbors.begin();
			iterAdj != v.neighbors.end(); ++iterAdj)
		{
			if ((*iterAdj)->distance == 2147000000)
			{
				(*iterAdj)->distance = v.distance + 1;
				(*iterAdj)->path = &vertices[v.id];
				q.push(**iterAdj);
			}
		}
	}
}

// prints all the vertex ids along the path from the start vertex of the last 
void graph::printPath(int end)
{
	//Store everything in a stack
	stack<int> ids;
	vertex v = vertices[end];
	ids.push(v.id);
	while (v.path != NULL)
	{
		v = *(v.path);		//Do it in this order to include the start vertex
		ids.push(v.id);
	}
	
	//Then print it all out in reverse order
	cout << "Here is the path through the maze: " << endl;
	while (!ids.empty())
	{
		cout << ids.top() << endl;
		ids.pop();
	}
}
