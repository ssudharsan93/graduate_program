#ifndef VERTEX_H
#define VERTEX_H

#include <map>
#include <string>

class Vertex {
private:
    string name;
    map<Vertex*, int> neighbors; // gives neighbor vertices and the index of the 
                                 // edge that corresponds to the vertex pair

public:
    Vertex(string name);
    is_neighbor(Vertex *vertex_to_check);
}

#endif VERTEX_H