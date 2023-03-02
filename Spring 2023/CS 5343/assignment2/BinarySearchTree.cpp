#include "BinarySearchTree.h"

// TreeNode Methods
void TreeNode::get_left_child();
void TreeNode::get_right_child();
void TreeNode::get_parent();
void TreeNode::set_left_child();
void TreeNode::set_right_child();
void TreeNode::set_parent();

// Binary Search Tree Methods
void BinarySearchTree::get_root();
void BinarySearchTree::set_root();
void BinarySearchTree::insert_node();
void BinarySearchTree::delete_node();
void BinarySearchTree::inorder_traversal(); // print after left child call
void BinarySearchTree::preorder_traversal(); // print before left child or right child call
void BinarySearchTree::postorder_traversal(); // print after left child and right child call return
void BinarySearchTree::print_tree();

