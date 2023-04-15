#include "Vertex.h"

Vertex::Vertex(string name, int index){
    this->name = name;
    this->index = index;
    this->adjacent_nodes = new vector<Vertex*>();
    this->incident_edges = new vector<Edge*>();
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
vector<Edge*>* Vertex::get_incident_edges(){
    return this->incident_edges;
}