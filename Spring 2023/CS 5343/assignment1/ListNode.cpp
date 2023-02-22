#include "ListNode.h"

// default constructor
ListNode::ListNode(){
    this->val = 0;
    this->next = NULL;
}

// constructor with an int value passed in as a parameter.
ListNode::ListNode(int value){
    this->val = value;
    this->next = NULL;
}

// gets the pointer to the next element
// pointed to by the list node's next pointer
ListNode* ListNode::get_next(){
    return this->next;
}

// sets the pointer to the next element
// pointed to by the list node's next pointer
void ListNode::set_next(ListNode *next_node){
    this->next = next_node;
}

// returns the value contained in the list node
int ListNode::get_val(){
    return this->val;
}

//sets the value contained in the list node
void ListNode::set_val(int value){
    this->val = value;
}

// Prints all the nodes, until NULL
// is reached. We can print a partial
// LinkedList or if this method is
// called with head the entire LinkedList is
// printed out.
void ListNode::print_values() {

    if (this->get_next() == NULL) {
        return;
    }

    ListNode *elem = this;
    cout << elem->get_val();
    elem = elem->get_next();

    while ( elem != NULL ){
        cout << " -> " << elem->get_val();
        elem = elem->get_next();
    }

    cout << endl;

}

//Since this method is pass by reference we don't need
// to return anyything.
void swap(ListNode *first, ListNode *second) {

    // set the first element's next pointer to
    // point to the element that is pointed to
    // by second's next pointer.
    first->set_next(second->get_next());

    //set the second element's next pointer to
    //point to the first element.
    second->set_next(first);

}

ListNode* bubble_sort(ListNode *head, int size){
    if (head->get_next() == NULL) {
        return head;
    }

    ListNode *prev;
    ListNode *current;
    ListNode *next;

    int main_counter = size;

    for ( int pass_cnter = 0; pass_cnter < size; pass_cnter++ ){
          // There should be a pass for each element in the Linked List.

          prev = NULL; // start off with head so prev will be NULL
          current = head; // current ListNode being looked at will be head
          next = head->get_next(); // first next element will be the ListNode after head

          cout << "\tPass : " << ( pass_cnter + 1 ) << endl;

          for ( int sort_cnter = 0; sort_cnter < main_counter; sort_cnter++ ){
              // main_counter indicates the number of remaining elements to be sorted.

              if ( current->get_val() > next->get_val() ) {
                  // if current is larger than the next value
                  // perform a swap
                  swap(current, next);

                  if ( prev == NULL ) {
                    // if prev is null we are swapping the two first elements
                    // so head should point to the new first element.
                    head = next;
                  }
                  else {
                    // otherwise we want prev to point to the new current element
                    // which would be next after current and next are swapped.
                    prev->set_next(next);
                  }

                  current = next;

              }

              cout << "\t\t";
              head->print_values();

              // if the element after next is NULL, then break out of the
              // loop. i.e. we have done all the sorting necessary
              if ( current->get_next()->get_next() == NULL ){
                break;
              }

              // prev points to the new list node which is
              // contained in current.
              prev = current;

              // current points to the new list node which is
              // after prev.
              current = prev->get_next();

              // next points to the new list node which is
              // after current.
              next = current->get_next();

          }

          cout << endl;

          // decrease the number of elements that need to be sorted by 1
          main_counter = main_counter - 1;

    }

    return head;
}
