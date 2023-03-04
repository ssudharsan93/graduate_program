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

void connect(TreeNode *parent, TreeNode *child, bool is_left_child) {

    if ( child != NULL ) {
        child->set_parent(parent);
    }

    if ( is_left_child ) { 
        parent->set_left_child(child);
    } else { 
        parent->set_right_child(child);
    }

}

TreeNode* replace( TreeNode *in, TreeNode *out ) {

    TreeNode *parent = out->get_parent();

    if ( parent == NULL ) { // deleting root...
        out->get_left_child()->set_parent(in);
        out->get_right_child()->set_parent(in);
    } 

    else { 
        if ( out->get_val() < parent->get_val() ) {
            parent->set_left_child(in);
        }
        else { 
            parent->set_right_child(in);
        }
    }

    in->set_parent(parent);
    in->set_left_child(out->get_left_child());
    in->set_right_child(out->get_right_child());

    return in;
}

// Binary Search Tree Methods

TreeNode* insert_node(TreeNode *root, int val){

    TreeNode* prev_node = NULL;
    TreeNode* current_node = root;

    while ( current_node != NULL ) { // Search till you reach closest leaf node     
        if ( val <= current_node->get_val() ) {
            prev_node = current_node;
            current_node = current_node->get_left_child();
        } 
            
        else {
            prev_node = current_node;
            current_node = current_node->get_right_child();
        }
    }

    if ( prev_node == NULL ){ // Inserting at Root
        root = new TreeNode(val);
        return root;
    } 

    else { 
    
        if ( val < prev_node->get_val() ) { // Node is less than Parent
            current_node = new TreeNode(val);
            current_node->set_parent(prev_node);
            prev_node->set_left_child(current_node);
        } 
        
        else if ( val > prev_node->get_val() ) { // Node is more than Parent
            current_node = new TreeNode(val);
            current_node->set_parent(prev_node);
            prev_node->set_right_child(current_node);
        }

        else { // An equal node is found.
            return prev_node;
        }

    }

    return current_node;

}

TreeNode* delete_node(TreeNode *root, int val){

    TreeNode *parent_current_node = NULL;
    TreeNode *current_node = root;

    while ( current_node != NULL && current_node->get_val() != val ) {
        if ( val < current_node->get_val() ) {
            parent_current_node = current_node;
            current_node = current_node->get_left_child();
        }

        else {
            parent_current_node = current_node;
            current_node = current_node->get_right_child();
        }
    }

    if ( current_node == NULL ) { return root; } // Didn't find the element. Returns root

    if ( current_node->get_left_child() == NULL && current_node->get_right_child() == NULL ) {
        if ( parent_current_node->get_right_child() == current_node ) { // right leaf node
            parent_current_node->set_right_child(NULL);
        }
        else { // left leaf node
                parent_current_node->set_left_child(NULL);
        }
        current_node->set_parent(NULL);
    } 

    else if ( current_node->get_left_child() == NULL && current_node->get_right_child() != NULL ) {
        
        TreeNode *successor = get_successor(current_node);

        connect(successor->get_parent(), successor->get_right_child(), true);
        TreeNode *new_node = replace(successor, current_node);

        if ( new_node->get_parent() == NULL ) {
            root = new_node;
        }

        // if ( parent_current_node == NULL ) { // deleting root...

        //     // replace(successor, root, true)
        //     root->get_left_child()->set_parent(successor);
        //     root->get_right_child()->set_parent(successor);
        //     successor->set_left_child(root->get_left_child());
        //     successor->set_right_child(root->get_right_child());
        //     root = successor;
        
        // } else { // deleting middle node...

        //     // replace(successor, current_node, true)
        //     if ( val > parent_current_node->get_val() ) { 
        //         parent_current_node->set_right_child(successor); 
        //     } // deleting a right child...

        //     // replace(successor, current_node, false)
        //     else { 
        //         parent_current_node->set_left_child(successor); 
        //     } // deleting a left child... 
        //     successor->set_parent(parent_current_node);
        //     successor->set_left_child(current_node->get_left_child());
        //     successor->set_right_child(current_node->get_right_child());

        // }

    }

    else { 
        
        TreeNode* predecessor = get_predecessor(current_node);

        connect(predecessor->get_parent(), predecessor->get_left_child(), false);
        
        TreeNode *new_node = replace(predecessor, current_node);

        if ( new_node->get_parent() == NULL ) {
            root = new_node;
        }

        // if ( parent_current_node == NULL ) { // deleting root...
        
        //     root->get_left_child()->set_parent(predecessor);
        //     root->get_right_child()->set_parent(predecessor);
        //     predecessor->set_left_child(root->get_left_child());
        //     predecessor->set_right_child(root->get_right_child());
        //     root = predecessor;
        
        // } else { // deleting a middle node...

        //     if ( val > parent_current_node->get_val() ) { 
        //         parent_current_node->set_right_child(predecessor); 
                
        //     } // deleting a right child...
        //     else { 
        //         parent_current_node->set_left_child(predecessor); 
        //     } // deleting a left child...

        //     predecessor->set_left_child(current_node->get_left_child());
        //     predecessor->set_right_child(current_node->get_right_child());
        //     predecessor->set_parent(parent_current_node);

        // }

    }

    return root;

}

TreeNode* get_successor(TreeNode *node) {

    TreeNode *current_node;

    if ( node->get_right_child() == NULL ) {
        current_node = node;
        while ( current_node->get_parent() != NULL &&
                current_node->get_parent()->get_left_child() != current_node ){
            current_node = current_node->get_parent();
        }

        current_node = current_node->get_parent();
    } 
    
    else {
        current_node = node->get_right_child();

        while ( current_node->get_left_child() != NULL ) {
            current_node = current_node->get_left_child();
        }
    }

    return current_node;

}

TreeNode* get_predecessor(TreeNode *node) {

    TreeNode *current_node;

    if ( node->get_left_child() == NULL ) {
        current_node = node;
        while ( current_node->get_parent() != NULL &&
                current_node->get_parent()->get_right_child() != current_node ){
            current_node = current_node->get_parent();
        }

        current_node = current_node->get_parent();
    } 
    
    else {
    
        current_node = node->get_left_child();
        while ( current_node->get_right_child() != NULL ) {
            current_node = current_node->get_right_child();
        }
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

