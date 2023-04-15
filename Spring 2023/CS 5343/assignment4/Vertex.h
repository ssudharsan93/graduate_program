#ifndef VERTEX_H
#define VERTEX_H

#include <map>
#include <string>
#include <vector>

#include "Edge.h"

class Edge;

using namespace std;

class Vertex {
private:
    string name;
    int index;
    vector<Vertex*> *adjacent_nodes;
    vector<Edge*> *incident_edges;

public:
    Vertex(string name, int index);
    string get_name();
    int get_index();
    bool is_adjacent(Vertex *vertex_to_check);
    vector<Edge*>* get_incident_edges();
};

#endif VERTEX_H