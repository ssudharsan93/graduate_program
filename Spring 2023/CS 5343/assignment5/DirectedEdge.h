#ifndef DIRECTEDEDGE_H
#define DIRECTEDEDGE_H

#include "Vertex.h"

class Vertex;

class DirectedEdge {
private:
    Vertex* origin;
    Vertex* destination;
    int index;
    int weight;

public:
    DirectedEdge(Vertex *origin, Vertex *destination, int index, int weight);
    int get_index();
    int get_weight();
    Vertex* get_origin();
    Vertex* get_destination();
    Vertex* opposite_vertex(Vertex *curr_vertex);
    void print_directed_edge();
};

#endif DIRECTEDEDGE_H