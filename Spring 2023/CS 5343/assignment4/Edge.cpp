    #include "Edge.h"

    Edge::Edge(Vertex *vertex1, Vertex *vertex2, int index, int weight){
    
        this->first_end_vertex = vertex1;
        this->second_end_vertex = vertex2;
        this->index = index;
        this->weight = weight;

    }
    
    int Edge::get_index(){
        return this->index;
    }

    int Edge::get_weight(){
        return this->weight;
    }
    
    Vertex* Edge::get_first_end_vertex(){
        return this->first_end_vertex;
    }
    
    Vertex* Edge::get_second_end_vertex(){
        return this->second_end_vertex;
    }
    
    Vertex* Edge::opposite_vertex(Vertex *curr_vertex){
        if ( this->first_end_vertex == curr_vertex ){
            return first_end_vertex;
        } else { 
            return second_end_vertex;
        }
    }

    void Edge::print_edge(){
        cout << "\tEdge " << this->index << " - ";
        cout << "\tEnd Vertex 1: " << this->first_end_vertex->get_name();
        cout << "\tEnd Vertex 2: " << this->second_end_vertex->get_name();
        cout << "\tWeight: "<< this->weight << endl;
    }
    