/****************************************************
 * vertex.h
 *
 *    -Paul Ngo (20522822)
 *    -Aidan Yamada (20524738)
 *    -Iain Klotzbach (20529667)
 *    -Ben Huynh (20518182)
 *
 ****************************************************/

#ifndef VERTEX_H
#define VERTEX_H

#include "edge.h"

class vertex{
    private:
       int prev; //Stores the previouis vertex in the shortest path
       double distance; //Holds the current distance

    public:
        int getPrev();
        void setPrev(int);
        double getDistance();
        void setDistance(double);
};

// Gets the vertex's predecessor, which is the previous vertex along the
// shortest path from the start vertex
int vertex::getPrev()
{
    return prev;
}

// Sets the vertex's predecessor.
void vertex::setPrev(int p)
{
    prev = p;
}

//Gets the distance from the start vertex. Determines the next vertex to visit
double vertex::getDistance()
{
    return distance;
}
//Sets distance from the start vertex to the current vertex
void vertex::setDistance(double d)
{
    distance = d;
}

#endif
