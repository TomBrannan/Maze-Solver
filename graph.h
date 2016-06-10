// graph.h - an undirected graph implemented with adjacency lists

#include <vector>
#include <list>
#include <queue> //used for the breadthFirst search method
#include <iostream> //used for printing the final path
#include <stack> //used for printing the final path in order
using namespace std;

struct vertex  // information stored per vertex
{ 
	int id;        // unique identifier for each vertex and its position in a graph's vertices vector
	bool known;    // whether the path from a start vertex to this vertex is currently known
	int distance;  // the shortest path length found to this vertex from a start vertex (so far)
	vertex *path;  // ptr to the vertex that preceeds this vertex along a shortest path to it
	list<vertex*> neighbors;  // pointers to vertices that can be reached from this vertex along a single edge
};

class graph  
{
	public:
		// member functions 
		void addVertex();                    // adds a vertex to the graph and assign it the next available id
		void addEdge(int id1, int id2);      // adds an undirected edge between vertices with the given ids
		void breadthFirst(int start);        // conducts a breadth-first search from the vertex with the specified id
		void printPath(int end);             // prints all the vertex ids along the path from the start vertex of the last 
		                                     // search to this end vertex (includes end points)
		
	//private:
		// data member - needs to be public for the graphics code to work:
		vector<vertex> vertices; // the graph - a vector of vertices, each of which stores a list of pointers to its neighbors

};
