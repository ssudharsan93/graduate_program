#ifndef EDGE_H
#define EDGE_H

#include <vector>

class Edge {
private:
Vertex* vertex1;
Vertex* vertex2;
int index;
int cost;

public:
    Edge(Vertex *vertex1, Vertex *vertex2, int index, int cost);
    get_index();
    get_vertex1();
    get_vertex2();
}

#endif EDGE_H