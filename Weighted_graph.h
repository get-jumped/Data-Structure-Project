/*****************************************

 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of those students
 * I had worked together in preparing this project:
 *    -Paul Ngo (20522822)
 *    -Aidan Yamada (20524738)
 *    -Iain Klotzbach  (20529667)
 *    -Ben Huynh (20518182)
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>

using namespace std;

// include whatever classes you want
#include <vector>
#include <stdexcept>
#include "vertex.h"
#include "edge.h"
#include "Exception.h"


class Weighted_graph {
    private:
		//A variable to hold an array of each vertex
		vertex* vertices;

        //2d array where the row index represents a vertex and the column index
        //represents an edges that the vertex is connected to
		vector<vector<edge>> edges;

        //keeps track of size of the array of vertices
		int len;

        //keeps track of the number of edges in the count
		int edgeCount;

		static const double INF;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int );

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

/* Weighted_graph constructor

initializes variables to default values

n is an int that represents the number of vertices in the graph

To handle errors if n is less than or equal to 0 there is an if
statement to set len to 1.

*/
Weighted_graph::Weighted_graph(int n)
{
    edgeCount = 0;

    //Checks to make sure that the number of vertices is greater than 0
	if (n <= 0)
    {
        len = 1;
    }
    else
    {
        len = n;
    }

    //Dynamically creates an array of vertex for the graph
    vertices = new vertex[len];

    //populates a vector with vector<edge> to keep track of the edges in
    //the graph
    for(int i = 0; i < len; i++)
    {
        edges.push_back(vector<edge>());
    }
}

//Destructor. Deletes the array of vertices and assigns it to nullptr.
//No parameters.
Weighted_graph::~Weighted_graph()
{
    //deletes the dynamically allocated array of vertex
    delete[] vertices;
    vertices = nullptr;
}

/* degree

Returns the degree of a vertex n. If n is not a valid vertex, then the
function throws an illegal_argument exception. If n is a valid vertex,
then the function returns the degree of n.

*/
int Weighted_graph::degree(int n) const
{
    if(n >= len || n < 0)
        throw illegal_argument();
    else
        return edges[n].size();
}

//edge_count() returns the number of edges in the graph
int Weighted_graph::edge_count() const
{
	return edgeCount;
}

/* adjacent

Return the weight of the edge between vertex n and m. If n and m are not
valid vertices, then the function throws an illegal_argument exception.
If n and m are valid vertices, then the function returns the weight of the
edge between n and m.

*/
double Weighted_graph::adjacent(int m, int n) const
{
    if(m >= len || m < 0)
        throw illegal_argument();
    else if(n >= len || n < 0)
        throw illegal_argument();

    //If the vertices are the same return 0
    if(m == n)
        return 0;

    //A loop that goes through the list of edges for vertex m and if an edge is found that connects it to n it returns the
    //weight of the edge
    vector<edge> adjacent = edges[m];
    for(int i = 0; i < adjacent.size(); i++)
    {
        if(n == adjacent[i].getToVertex())
            return adjacent[i].getWeight();
    }
	return INF;
}

/* distance

This function uses Dijkstra's algorithm to calculate the shortest distance
between two vertices.

m is an int that represents the starting vertex
n is an int that represents the ending vertex

This function assumes that the vertices array is already initialized and
the value to indicate that a vertex doesn't have a previous vertex is -1.

To handle errors with m and n by throwing an illegal_argument exception
when m or n references a vertex that doesn't exist in the graph

*/
double Weighted_graph::distance(int m, int n)
{
    if(m >= len || m < 0)
        throw illegal_argument();
    else if(n >= len || n < 0)
        throw illegal_argument();

    //sets all the prev variables for vertex to -1 meaning that it has no previous vertex
    //and distance to infinity
    for(int i = 0; i < len; i++)
    {
        vertices[i].setPrev(-1);
        vertices[i].setDistance(INF);
    }

    //Sets the starting vertex distance to 0
    vertices[m].setDistance(0);

    //variables to keep track of the loop
    int counter = 0;
    double path = 0;
    double edgeWeight;
    vector<edge> temp;

    //loop that runs while not all the vertices have been visited
    while(counter < len)
    {
        //sets the list of edges at vertex m + counter to temp
        temp = edges[(m + counter) % len];

        //loop that sets the distance variable for each vertex to find the
        //shortest path
        for(int i = 0; i < temp.size(); i++)
        {
            edgeWeight = temp[i].getWeight();
            path = vertices[(m + counter) % len].getDistance() + edgeWeight;

            if(path < vertices[temp[i].getToVertex()].getDistance())
            {
                vertices[temp[i].getToVertex()].setDistance(path);
                vertices[temp[i].getToVertex()].setPrev(i);
            }
        }
        counter++;
    }

	return vertices[n].getDistance();
}

/* insert

This function inserts an edge into the graph. This is achieved by first
checking if the edge already exists in the graph and if is the weight is
changed to the new passed in weight. If the edge doesnt already exist
edgeCount is incremented and the new edge is added to the vectors that hold
the edges that connect to vertices m and n.

m is an int that represents the starting vertex
n is an int that represents the ending vertex
w is a double that is the weight of the edge

This function makes the assumption that the edges vector has been initialized

This function handles error pertaining to invalid arguments by throwing an
illegal_argument and printing out what variable caused the issue.
*/

void Weighted_graph::insert(int m, int n, double w)
{
    if(m >= len || m < 0)
        throw illegal_argument();
    else if(n >= len || n < 0)
        throw illegal_argument();
    else if(w <= 0 || w == INF)
        throw illegal_argument();


    //variables to keep track of the loop
    bool exists = false;
    int counter = 0;

    //loop that checks if the edge already exists and if it does replaces the
    //weight with the new passed in value
    while(exists == false && counter < edges[m].size())
    {
        if(edges[m][counter].getToVertex() == n)
        {
            exists = true;
            edges[m][counter].setWeight(w);
            for(int j = 0; j < edges[n].size(); j++)
            {
                if(edges[n][j].getToVertex() == m)
                    edges[n][j].setWeight(w);
            }
        }
        counter++;
    }

    //if the edge is not found it addes the edge to vertices vectors
    if(exists == false)
    {
        edgeCount++;
        edges[m].push_back(edge(n, w));
        edges[n].push_back(edge(m, w));
    }
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in CIS22B.h or elsewhere?
// Did you forget a closing '}' ?

#endif
