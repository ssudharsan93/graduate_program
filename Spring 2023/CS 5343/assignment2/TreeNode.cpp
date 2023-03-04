#include "TreeNode.h"

using namespace std;

TreeNode::TreeNode(int val) {
    this->left_child = NULL;
    this->right_child = NULL;
    this->parent = NULL;
    this->val = val;
}

// TreeNode Methods
TreeNode* TreeNode::get_left_child(){
    return this->left_child;
}

TreeNode* TreeNode::get_right_child(){
    return this->right_child;
}

TreeNode* TreeNode::get_parent(){
    return this->parent;
}

void TreeNode::set_left_child(TreeNode *new_left_child){
    this->left_child = new_left_child;
}

void TreeNode::set_right_child(TreeNode *new_right_child){
    this->right_child = new_right_child;
}

void TreeNode::set_parent(TreeNode *new_parent){
    this->parent = new_parent;
}

int TreeNode::get_val() {
    return this->val;
}

// Binary Search Tree Methods

TreeNode* insert_node(TreeNode *root, int val){

    TreeNode* prev_node = NULL;
    TreeNode* current_node = root;

    while ( current_node != NULL ) {            
        if ( val <= current_node->get_val() ) {
            prev_node = current_node;
            current_node = current_node->get_left_child();
        } 
            
        else {
            prev_node = current_node;
            current_node = current_node->get_right_child();
        }
    }

    if ( prev_node == NULL ){
        root = new TreeNode(val);
        current_node = root;
    } 
    
    else if ( val <= prev_node->get_val() ) {
        current_node = new TreeNode(val);
        current_node->set_parent(prev_node);
        prev_node->set_left_child(current_node);
    } 
    
    else {
        current_node = new TreeNode(val);
        current_node->set_parent(prev_node);
        prev_node->set_right_child(current_node);
    }

    return current_node;

}

TreeNode* delete_node(TreeNode *root, int val){

    TreeNode *prev_node = NULL;
    TreeNode *current_node = root;

    while ( current_node->get_val() != val  && current_node != NULL ) {
        if ( val < current_node->get_val() ) {
            prev_node = current_node;
            current_node = current_node->get_left_child();
        }

        else {
            prev_node = current_node;
            current_node = current_node->get_left_child();
        }
    }

    if ( current_node == NULL ) { return root; }

    if ( current_node->get_left_child() == NULL && current_node->get_right_child() == NULL ) {
        if ( val > prev_node->get_val() ) { // right leaf node
            prev_node->set_right_child(NULL);
            current_node->set_parent(NULL);
        }

        else { // left leaf node
                prev_node->set_left_child(NULL);
                current_node->set_parent(NULL);
        }
    } 

    else if ( current_node->get_left_child() == NULL && current_node->get_right_child() != NULL ) {
        
        TreeNode* successor = get_successor(current_node);

        successor->get_parent()->set_left_child(successor->get_right_child());

        if ( successor->get_right_child() != NULL ) {
            successor->get_right_child()->set_parent(successor->get_parent());
        }

        if ( prev_node == NULL ) { // deleting root...
        
            root->get_left_child()->set_parent(successor);
            root->get_right_child()->set_parent(successor);
            successor->set_left_child(root->get_left_child());
            successor->set_right_child(root->get_right_child());
            root = successor;
        
        } else {

            if ( val > prev_node->get_val() ) { 
                prev_node->set_right_child(successor); 
            } // deleting a right child...
            else { 
                prev_node->set_left_child(successor); 
            } // deleting a left child... 
            successor->set_parent(prev_node);
            successor->set_left_child(current_node->get_left_child());
            successor->set_right_child(current_node->get_right_child());

        }

    }

    else { 
        
        TreeNode* predecessor = get_predecessor(current_node);

        predecessor->get_parent()->set_right_child(predecessor->get_left_child());
        
        if ( predecessor->get_left_child() != NULL ) {
            predecessor->get_left_child()->set_parent(predecessor->get_parent());
        }

        if ( prev_node == NULL ) { // deleting root...
        
            root->get_left_child()->set_parent(predecessor);
            root->get_right_child()->set_parent(predecessor);
            predecessor->set_left_child(root->get_left_child());
            predecessor->set_right_child(root->get_right_child());
            root = predecessor;
        
        } else {

            if ( val > prev_node->get_val() ) { 
                prev_node->set_right_child(predecessor); 
                
            } // deleting a right child...
            else { 
                prev_node->set_left_child(predecessor); 
            } // deleting a left child...

            predecessor->set_left_child(current_node->get_left_child());
            predecessor->set_right_child(current_node->get_right_child());
            predecessor->set_parent(prev_node);

        }

    }

    return root;

}

TreeNode* get_successor(TreeNode *node) {

    if ( node->get_right_child() == NULL ) { return NULL; }
    
    TreeNode *current_node = node->get_right_child();

    while ( current_node->get_left_child() != NULL ) {
        current_node = current_node->get_left_child();
    }

    return current_node;

}

TreeNode* get_predecessor(TreeNode *node) {

    if ( node->get_left_child() == NULL ) { return NULL; }
    
    TreeNode *current_node = node->get_left_child();

    while ( current_node->get_right_child() != NULL ) {
        current_node = current_node->get_right_child();
    }

    return current_node;
}

void inorder_traversal(TreeNode *node){
    
    if (node == NULL) { return; }
    
    inorder_traversal(node->get_left_child());
    cout << node->get_val() << " ";
    inorder_traversal(node->get_right_child());

    return;

}// print after left child call

void preorder_traversal(TreeNode *node){

    if ( node == NULL ) { return; }

    cout << node->get_val() << " ";
    inorder_traversal(node->get_left_child());
    inorder_traversal(node->get_right_child());


} // print before left child or right child call

void postorder_traversal(TreeNode *node){
    
    inorder_traversal(node->get_left_child());
    inorder_traversal(node->get_right_child());
    cout << node->get_val() << " ";

    return;
} // print after left child and right child call return

void print_tree(){
    return;
}

