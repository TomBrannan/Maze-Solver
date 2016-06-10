// maze.cpp - solves a maze read from a text file using a breadth-first search on a graph representing the maze

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "glut.h"	// GLUT Library (for graphics and user interaction)
#include "graph.h" // graph class

// Global constants & variables
const int CLEAR = 0;
int rows;
int columns;
int cellsCount; // # cells in maze (== # vertices in graph)

int mazeArray[50][50];
graph mazeGraph;
ifstream stream;
string filename;

// forward declaration - function called by graphics code included below
void solveMazeAndPrintPath();

#include "graphics.h" // application-specific graphics functions, uses global vars defined above

void createGraphFromMazeFile()
{ 
	ifstream stream;

	do
	{
		cout << "Enter the maze file you wish to view: ";
		cin >> filename;
		stream.open(filename);
	} while (!stream);

	//Read the rows and columns, and calculate cellsCount
	stream >> rows;
	stream >> columns;
	cellsCount = rows * columns;

	//Read until the end of the file, initializing mazeArray data and graph's vertices.
	//Assumes proper structure of the maze file
	for (int i = 0; !stream.eof() && i < rows; i++)
	{
		for (int j = 0; !stream.eof() && j < columns; j++)
		{
			stream >> mazeArray[i][j];
			mazeGraph.addVertex();
		}
	}
	stream.close();

	//Initialize our graph's edge data by checking each vertex, one at a time
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (mazeArray[i][j] == CLEAR) //Only proceed if this vertex is clear
			{
				int thisID = i * columns + j; //The ID of this vertex
				if (i != 0 && mazeArray[i - 1][j] == CLEAR) //Check north
				{
					int northID = (i - 1) * columns + j;
					mazeGraph.addEdge(thisID, northID);
				}
				if (i != (rows - 1) && mazeArray[i + 1][j] == CLEAR) //Check south
				{
					int southID = (i + 1) * columns + j;
					mazeGraph.addEdge(thisID, southID);
				}
				if (j != 0 && mazeArray[i][j - 1] == CLEAR) // Check west
				{
					int westID = i * columns + j - 1;
					mazeGraph.addEdge(thisID, westID);
				}
				if (j != columns - 1 && mazeArray[i][j + 1] == CLEAR) // Check east
				{
					int eastID = i * columns + j + 1;
					mazeGraph.addEdge(thisID, eastID);
				}
			}
		}
	}
}  

//The call to breadthFirst() modifies the graph's vertices to find a path from the 
//start to each vertex.  This information is later used to print the shortest
//path from the starting vertex to an arbitrary ending vertex.
void solveMazeAndPrintPath()
{
	/*We assume the start point is at row 2, column 1.  The ID of this vertex will
	be == columns as long as the vertices are 0-indexed and sequential.  We also
	assume the finish point is in the rightmost column, second-to-last row.*/
	mazeGraph.breadthFirst(columns);
	mazeGraph.printPath(cellsCount - columns - 1);
}

int main(int argc, char** argv)
{
	createGraphFromMazeFile(); // reads the maze file and initializes all global variables	      
	startGraphicsLoop(argc, argv);
   
    return 0;
}



