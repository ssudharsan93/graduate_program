#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

class Edge {
private:
    Vertex* first_end_vertex;
    Vertex* second_end_vertex;
    int index;
    int weight;

public:
    Edge(Vertex *vertex1, Vertex *vertex2, int index, int cost);
    int get_index();
    Vertex* get_first_end_vertex();
    Vertex* get_second_end_vertex();
    Vertex* opposite_vertex(Vertex *curr_vertex);
};

#endif EDGE_H