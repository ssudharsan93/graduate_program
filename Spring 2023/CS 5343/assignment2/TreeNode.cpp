#include "TreeNode.h"

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

    else if ( current_node->get_left_child() == NULL && current_node->get_right_child() != NULL ) { // replace with successor
                                                                                                    // if predecessor doesn't exist.    
        TreeNode *successor = get_successor(current_node);

        connect(successor->get_parent(), successor->get_right_child(), true);
        TreeNode *new_node = replace(successor, current_node);

        if ( new_node->get_parent() == NULL ) {
            root = new_node;
        }

    }

    else { // replace with predecessor 
        
        TreeNode* predecessor = get_predecessor(current_node);

        connect(predecessor->get_parent(), predecessor->get_left_child(), false);
        TreeNode *new_node = replace(predecessor, current_node);

        if ( new_node->get_parent() == NULL ) {
            root = new_node;
        }

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

void breadth_first_search(TreeNode *node, queue<TreeNode*> *to_be_searched, queue<TreeNode*> *searched) {

    TreeNode* current_node;

    if ( node->get_parent() == NULL && to_be_searched->size() == 0) { //node is root
        to_be_searched->push(node);
    }

    else { 
        // enqueuing children

        if ( node->get_left_child() != NULL ) {
            to_be_searched->push(node->get_left_child());
        }

        if ( node->get_right_child() != NULL ) {
           to_be_searched->push(node->get_right_child());
        }
        
        // dequeuing parent from to_be_searched
        current_node = to_be_searched->front();
        to_be_searched->pop();

        // enqueuing parent in searched
        searched->push(current_node);
    }

    while ( to_be_searched->size() != 0 ) {
        current_node = to_be_searched->front();
        breadth_first_search(current_node, to_be_searched, searched);
    }

    return;

}

int get_node_count(TreeNode *node) {
    if ( node == NULL ) {
        return 0;
    }
    else {
        TreeNode *lch = node->get_left_child();
        TreeNode *rch = node->get_right_child();

        return 1 + get_node_count(lch) + get_node_count(rch);
    }
    
}

void print_tree(TreeNode *root){

    queue<TreeNode*> *to_be_searched = new queue<TreeNode*>();
    queue<TreeNode*> *searched = new queue<TreeNode*>();
    breadth_first_search(root, to_be_searched, searched);

    int dft_search_size = searched->size();

    TreeNode *current_node;
    int num_of_children = 0;
    int max_num_of_nodes_of_any_level = 0;
    int num_of_nodes = 1;

    int dft_search_content_cntr = 0;
    int level_end_cntr;
    int level_cntr = 0;

    map<int, int> *level_node_count = new map<int, int>();
    level_node_count->insert(make_pair(level_cntr, num_of_nodes));   

    while ( dft_search_content_cntr < dft_search_size ) {

        level_end_cntr = dft_search_content_cntr + num_of_nodes;

        while ( dft_search_content_cntr < level_end_cntr ) {

            current_node = searched->front();
            searched->pop();
            cout << right << "    " << current_node->get_val();

            if ( current_node->get_left_child() != NULL ) { 
                num_of_children = num_of_children + 1; 
            }

            if ( current_node->get_right_child() != NULL ) { 
                num_of_children = num_of_children + 1; 
            }
            
            dft_search_content_cntr = dft_search_content_cntr + 1;

            searched->push(current_node);
        }

        cout << endl;

        if ( num_of_children > max_num_of_nodes_of_any_level ) {
            max_num_of_nodes_of_any_level = num_of_children;
        }

        level_cntr = level_cntr + 1;
        num_of_nodes = num_of_children;
        level_node_count->insert(make_pair(level_cntr, num_of_nodes));
        num_of_children = 0;
        
    }

    cout << endl;
    cout << "Width should correspond to : " << max_num_of_nodes_of_any_level << endl;
    cout << "Num Levels : " << level_cntr << endl;
    cout << "Size of Queue: " << searched->size() << endl;

    auto lvl_node_cnt_map_beg = level_node_count->begin();
    auto lvl_node_cnt_map_end = level_node_count->end();

    for ( auto lvl_node_cnt_map_it = lvl_node_cnt_map_beg; 
          lvl_node_cnt_map_it != lvl_node_cnt_map_end; 
          ++lvl_node_cnt_map_it ) {
        cout << "Level: " << lvl_node_cnt_map_it->first
             << " has " << lvl_node_cnt_map_it->second
             << " number of node " << endl;
    }

    cout << endl;

    return;
}

// Need to know the number of leaf nodes, thats the max width.
// Need to know whether that element is a child of a certain element.


