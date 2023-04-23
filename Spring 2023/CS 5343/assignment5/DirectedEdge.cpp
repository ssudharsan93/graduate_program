    #include "DirectedEdge.h"

    DirectedEdge::DirectedEdge(Vertex *origin, Vertex *destination, int index, int weight){
    
        this->origin = origin;
        this->destination = destination;
        this->index = index;
        this->weight = weight;

    }
    
    int DirectedEdge::get_index(){
        return this->index;
    }

    int DirectedEdge::get_weight(){
        return this->weight;
    }
    
    Vertex* DirectedEdge::get_origin(){
        return this->origin;
    }
    
    Vertex* DirectedEdge::get_destination(){
        return this->destination;
    }
    
    Vertex* DirectedEdge::opposite_vertex(Vertex *curr_vertex){
        if ( this->origin == curr_vertex ){
            return this->destination;
        } else { 
            return this->origin;
        }
    }

    void DirectedEdge::print_directed_edge(){
        cout << "\tEdge " << this->index << " - ";
        cout << "\t\t(Vertex " << this->origin->get_name();
        cout << " , Vertex " << this->destination->get_name();
        cout << ")\t\tWeight: "<< this->weight << endl;
    }
    
