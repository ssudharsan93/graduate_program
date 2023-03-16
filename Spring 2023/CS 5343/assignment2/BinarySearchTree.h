#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

class BinarySearchTree {
private:
    TreeNode *root;
public:
    BinarySearchTree();
    ~BinarySearchTree();
    TreeNode* insert_node(int val);
    TreeNode* delete_node(int val);
    TreeNode* get_successor(TreeNode *node);
    TreeNode* get_predecessor(TreeNode *node);
    void inorder_traversal(TreeNode *node); // print after left child call
    void preorder_traversal(TreeNode *node); // print before left child or right child call
    void postorder_traversal(TreeNode *node); // print after left child and right child call return
    void breadth_first_search(TreeNode *node, queue<TreeNode*> *to_be_searched, queue<TreeNode*> *searched);
    void print_tree();

}

#endif BINARYSEARCHTREE_H