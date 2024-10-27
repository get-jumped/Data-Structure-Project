/****************************************************
 * edge.h
 *
 *    -Paul Ngo (20522822)
 *    -Aidan Yamada (20524738)
 *    -Iain Klotzbach (20529667)
 *    -Ben Huynh (20518182)
 *
 ****************************************************/

#ifndef EDGE_H
#define EDGE_H

#include <vector>

class edge{
    private:
        int toVertex;
        double weight;

    public:
        edge(int, double);
        int getToVertex();
        double getWeight();
        void setToVertex(int);
        void setWeight(double);
};

// Sets a weighted edge between verticies
edge::edge(int n, double w)
{
    toVertex = n;
    weight = w;
}

// Returns the Vertex connected to the edge
int edge::getToVertex()
{
    return toVertex;
}

// Returns the edges weight
double edge::getWeight()
{
    return weight;
}

// Sets the vertex an edge is connected to
void edge::setToVertex(int v)
{
    toVertex = v;
}

// Sets the weight of edge to the passed in value w
void edge::setWeight(double w)
{
    weight = w;
}

#endif
