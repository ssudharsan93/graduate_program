#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Graph.h"

Graph* set_up_env() {

    srand(time(0));

    int *weights = new int[20]();
    float rand_val;
    int new_weight;

    for ( int weight_cntr = 0; weight_cntr < 20; weight_cntr++ ) {
        float rand_val = (float) rand() * 1.0 /( (float) RAND_MAX * 1.0 );
        cout << "Rand Val " << weight_cntr << " : " << rand_val << endl;
        new_weight = rand_val * 21;
        cout << "Weight " << weight_cntr << " : " << new_weight << endl;

        weights[weight_cntr] = new_weight;
    }
    
    Graph *dataset = new Graph();
    
    Vertex *a1 = new Vertex("A1", 0);
    Vertex *b1 = new Vertex("B1", 1);
    Vertex *c1 = new Vertex("C1", 2);
    Vertex *d1 = new Vertex("D1", 3);
    Vertex *e1 = new Vertex("E1", 4);
    Vertex *f1 = new Vertex("F1", 5);
    Vertex *g1 = new Vertex("G1", 6);
    Vertex *h1 = new Vertex("H1", 7);
    Vertex *i1 = new Vertex("I1", 8);
    Vertex *j1 = new Vertex("J1", 9);

    delete [] weights;

    return NULL;

    return dataset;
    
}

int main() {

    Graph *dataset = set_up_env();
}