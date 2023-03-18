#include <iostream>
#include <cmath>

using namespace std;

//HEAP METHODS_START
int Parent(int index) {
    return floor( index / 2.0 );
}

int Left(int index) {
    return 2 * index;
}

int Right(int index) {
    return 2 * index + 1;
}

void swap( int heap[], int first_index, int second_index ) {

    int temp = heap[first_index];
    heap[first_index] = heap[second_index];
    heap[second_index] = temp;

}

void PrintHeap(int heap[]) {

    int heap_size = heap[0];

    cout << "[ ";
    
    for ( int heap_cntr = 1; heap_cntr < heap_size + 1; heap_cntr++ ) {
        cout << heap[heap_cntr] << " ";
    }
    
    cout << "]" << endl;
}

void maxHeapify(int heap[], int index, int heap_size) {

    int left_child_index, right_child_index;

    left_child_index = Left(index);
    right_child_index = Right(index);

    while ( ! ( left_child_index > heap_size ) || 
             ! ( right_child_index > heap_size ) ) {

        // if parent is greater than both children heap property not violated.
        if ( ( heap[index] > heap[left_child_index] ) &&
             ( heap[index] > heap[right_child_index] ) ) {
                return;
        }

        // if only left child exists, swap if left child is greater than parent.
        // Then return right away. We are at a leaf node.
        if ( right_child_index > heap_size ) {
            if ( heap[index] < heap[left_child_index] ) {
                swap(heap, index, left_child_index);
            }
            return;

        }

        // if left child is less than right child
        // swap with right child otherwise swap with left child 
        // At this point either the left or right child is greater 
        // than the parent because of the prior if condition.

        int max_index = heap[left_child_index] > heap[right_child_index] ? left_child_index : right_child_index;
        swap(heap, index, max_index);
        index = max_index;

        left_child_index = Left(index);
        right_child_index = Right(index);
    }

}

//Floyds algorithm
void maxBuildHeap(int heap[]){
    
    int heap_size = heap[0];
    int left_child_index, right_child_index;

    for ( int bh_cntr = heap_size; bh_cntr > 0; bh_cntr-- ) {
        left_child_index = Left(bh_cntr);
        right_child_index = Right(bh_cntr);

        if ( ( left_child_index > heap_size ) && 
             ( right_child_index > heap_size ) ) {
            continue;
        }

        else { 
            maxHeapify(heap, bh_cntr, heap_size);
        }
    }


}

void minHeapify(int heap[], int index, int heap_size) {

    int left_child_index, right_child_index;

    left_child_index = Left(index);
    right_child_index = Right(index);

    while ( ! ( left_child_index > heap_size ) || 
             ! ( right_child_index > heap_size ) ) {

        // if parent is less than both children heap property not violated.
        if ( ( heap[index] < heap[left_child_index] ) &&
             ( heap[index] < heap[right_child_index] ) ) {
                return;
        }

        // if only left child exists, swap if left child is less than parent.
        // Then return right away. We are at a leaf node.
        if ( right_child_index > heap_size ) {
            if ( heap[index] > heap[left_child_index] ) {
                swap(heap, index, left_child_index);
            }
            return;
        }

        // if left child is greater than right child
        // swap with right child otherwise swap with left child 
        // At this point either the left or right child is less 
        // than the parent because of the prior if condition.

        int min_index = heap[left_child_index] < heap[right_child_index] ? left_child_index : right_child_index;
        swap(heap, index, min_index);
        index = min_index;

        left_child_index = Left(index);
        right_child_index = Right(index);
    }

}

//Floyds algorithm
void minBuildHeap(int heap[]){
    
    int heap_size = heap[0];
    int left_child_index, right_child_index;

    for ( int bh_cntr = heap_size; bh_cntr > 0; bh_cntr-- ) {
        left_child_index = Left(bh_cntr);
        right_child_index = Right(bh_cntr);

        if ( ( left_child_index > heap_size ) && 
             ( right_child_index > heap_size ) ) {
            continue;
        }

        else { 
            minHeapify(heap, bh_cntr, heap_size);
        }
    }

}

void minHeapSort(int heap[]){

    maxBuildHeap(heap);

    int heap_size = heap[0];

    int bh_cntr = heap_size;

    while ( bh_cntr > 0 ) {
        swap(heap, 1, bh_cntr);
        bh_cntr = bh_cntr - 1;
        maxHeapify(heap, 1, bh_cntr);
    }

    return;
}

void maxHeapSort(int heap[]){

    minBuildHeap(heap);

    int heap_size = heap[0];

    int bh_cntr = heap_size;

     while ( bh_cntr > 0 ) {        
        swap(heap, 1, bh_cntr);
        bh_cntr = bh_cntr - 1;
        minHeapify(heap, 1, bh_cntr);
    }

    return;
}

//HEAP METHODS_END



int main() {
    int heap_size = 15;
    int heap[heap_size + 1];
    int heap1[heap_size + 1];

    heap[0] = heap_size;
    heap1[0] = heap_size;

    int input[15] = {
        40, 60, 20, 80, 50, 
        10, 30, 15, 5, 35, 
        25, 45, 55, 70, 90
    };

    for ( int heap_cntr = 1; heap_cntr < heap_size + 1; heap_cntr++ ) {
        heap[heap_cntr] = input[heap_cntr - 1]; 
    }

    for ( int heap1_cntr = 1; heap1_cntr < heap_size + 1; heap1_cntr++ ) {
        heap1[heap1_cntr] = input[heap1_cntr - 1];
    }

    cout << endl;
    cout << "Array is: \t";
    cout << endl;
    PrintHeap(heap);
    
    minBuildHeap(heap);

    cout << endl;
    cout << "After Min BuildHeap / Floyd's Algorithm the Heap is: \t";
    cout << endl;
    PrintHeap(heap);

    // cout << endl;
    // cout << "Heap is: \t";
    // cout << endl;
    // PrintHeap(heap);

    // maxBuildHeap(heap);

    // cout << endl;
    // cout << "After Max BuildHeap the Heap is: \t";
    // cout << endl;
    // PrintHeap(heap);

    maxHeapSort(heap);

    cout << endl;
    cout << "After the Max Heapsort the Heap is: \t";
    cout << endl;
    PrintHeap(heap);

    cout << endl;

}



