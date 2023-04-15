#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

class Vertex;

class Edge {
private:
    Vertex* first_end_vertex;
    Vertex* second_end_vertex;
    int index;
    int weight;

public:
    Edge(Vertex *vertex1, Vertex *vertex2, int index, int weight);
    int get_index();
    int get_weight();
    Vertex* get_first_end_vertex();
    Vertex* get_second_end_vertex();
    Vertex* opposite_vertex(Vertex *curr_vertex);
    void print_edge();
};

#endif EDGE_H