#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Graph.h"

void print_matrix(int **matrix, int num_rows, int num_columns) {

    cout << "\t    ";
    for ( int col_index_cntr = 0; col_index_cntr < num_columns; col_index_cntr++ ){
        if ( col_index_cntr == 0 ) { cout << col_index_cntr; }
        else { cout << "    " << col_index_cntr; }
    }

    cout << "    " << endl;
    cout << endl;

    for ( int row_cntr = 0; row_cntr < num_rows; row_cntr++ ) {

        cout << "\t[   ";
        
        for ( int col_cntr = 0; col_cntr < num_columns; col_cntr++ ) {
            if ( col_cntr == 0 ) { cout << matrix[row_cntr][col_cntr]; }
            else { cout << ",   " << matrix[row_cntr][col_cntr]; }

        }

        cout << "   ]" << endl;

    }

}

Graph* create_and_insert_vertices_and_edges(Graph* dataset) {

    Vertex *a1 = new Vertex("A", 0);
    Vertex *b1 = new Vertex("B", 1);
    Vertex *c1 = new Vertex("C", 2);
    Vertex *d1 = new Vertex("D", 3);
    Vertex *f1 = new Vertex("F", 4);
    Vertex *g1 = new Vertex("G", 5);
    Vertex *h1 = new Vertex("H", 6);
    Vertex *i1 = new Vertex("I", 7);
    Vertex *j1 = new Vertex("J", 8);
    Vertex *k1 = new Vertex("K", 9);

    dataset->insert_vertex(a1);
    dataset->insert_vertex(b1);
    dataset->insert_vertex(c1);
    dataset->insert_vertex(d1);
    dataset->insert_vertex(f1);
    dataset->insert_vertex(g1);
    dataset->insert_vertex(h1);
    dataset->insert_vertex(i1);
    dataset->insert_vertex(j1);
    dataset->insert_vertex(k1);

    srand(time(0));

    int *weights = new int[20]();
    float rand_val;
    int new_weight;

    for ( int weight_cntr = 0; weight_cntr < 30; weight_cntr++ ) {
        float rand_val = (float) rand() * 1.0 /( (float) RAND_MAX * 1.0 );
        new_weight = rand_val * 20 + 1;
        weights[weight_cntr] = new_weight;
    }

    Edge *e0 = new Edge(a1, b1, 0, weights[0]);
    Edge *e1 = new Edge(a1, c1, 1, weights[1]);
    Edge *e2 = new Edge(a1, d1, 2, weights[2]);
    Edge *e3 = new Edge(b1, c1, 3, weights[3]);
    Edge *e4 = new Edge(c1, d1, 4, weights[4]);
    Edge *e5 = new Edge(b1, d1, 5, weights[5]);
    Edge *e6 = new Edge(b1, f1, 6, weights[6]);
    Edge *e7 = new Edge(c1, g1, 7, weights[7]);
    Edge *e8 = new Edge(d1, h1, 8, weights[8]);
    Edge *e9 = new Edge(c1, f1, 9, weights[9]);
    Edge *e10 = new Edge(d1, g1, 10, weights[10]);
    Edge *e11 = new Edge(f1, g1, 11, weights[11]);
    Edge *e12 = new Edge(g1, h1, 12, weights[12]);
    Edge *e13 = new Edge(f1, h1, 13, weights[13]);
    Edge *e14 = new Edge(f1, i1, 14, weights[14]);
    Edge *e15 = new Edge(g1, j1, 15, weights[15]);
    Edge *e16 = new Edge(h1, k1, 16, weights[16]);
    Edge *e17 = new Edge(g1, i1, 17, weights[17]);
    Edge *e18 = new Edge(h1, j1, 18, weights[18]);
    Edge *e19 = new Edge(i1, j1, 19, weights[19]);


    dataset->insert_edge(e0);
    dataset->insert_edge(e1);
    dataset->insert_edge(e2);
    dataset->insert_edge(e3);
    dataset->insert_edge(e4);
    dataset->insert_edge(e5);
    dataset->insert_edge(e6);
    dataset->insert_edge(e7);
    dataset->insert_edge(e8);
    dataset->insert_edge(e9);
    dataset->insert_edge(e10);
    dataset->insert_edge(e11);
    dataset->insert_edge(e12);
    dataset->insert_edge(e13);
    dataset->insert_edge(e14);
    dataset->insert_edge(e15);
    dataset->insert_edge(e16);
    dataset->insert_edge(e17);
    dataset->insert_edge(e18);
    dataset->insert_edge(e19);

    delete [] weights;

    
    return dataset;
}

Graph* set_up_env() {
    
    Graph *dataset = new Graph();

    dataset = create_and_insert_vertices_and_edges(dataset);
    
    dataset->print_vertices();
    dataset->print_edges();

    dataset->print_adjacent_vertices();

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "          Adjacency Matrix" << endl;
    cout << "---------------------------------" << endl;

    int **adjacency_matrix = dataset->get_adjacency_matrix();

    int matrix_n = dataset->get_vertices()->size();

    print_matrix(adjacency_matrix, matrix_n, matrix_n);

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << endl;

    return dataset;
    
}

int main() {

    Graph *dataset = set_up_env();

    dataset->run_dijkstras_algorithm_for_shortest_path();

}