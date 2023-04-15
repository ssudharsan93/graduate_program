#include "Vertex.h"

Vertex::Vertex(string name, int index){
    this->name = name;
    this->index = index;
    this->adjacent_nodes = new vector<Vertex*>();
    this->incident_edges = new vector<Edge*>();
}

Vertex::~Vertex(){
    delete this->adjacent_nodes;
    delete this->incident_edges;
}
    
string Vertex::get_name() {
    return this->name;
}

int Vertex::get_index(){
    return this->index;
}

bool Vertex::is_adjacent(Vertex *vertex_to_check){
    
    int vector_size = this->adjacent_nodes->size();
    
    for ( int vector_cntr = 0; vector_cntr < vector_size; vector_cntr++ ){
        if ( this->adjacent_nodes->at(vector_cntr) == vertex_to_check ){
            return true;
        }
    }

    return false;

}

void Vertex::add_adjacent_node(Vertex* adjacent_node) {
    this->adjacent_nodes->push_back(adjacent_node);
}

void Vertex::add_incident_edge(Edge* incident_edge) {
    this->incident_edges->push_back(incident_edge);
}

vector<Vertex*>* Vertex::get_adjacent_nodes(){
    return this->adjacent_nodes;
}

vector<Edge*>* Vertex::get_incident_edges(){
    return this->incident_edges;
}

void Vertex::print_vertex(){
    cout << "\t" << this->index << " : " << this->name << endl; 
}