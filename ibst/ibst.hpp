//
//  ibst.hpp
//  ibst
//
//  Created by Colin on 05/11/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#ifndef ibst_hpp
#define ibst_hpp

#include <iostream>
#include <vector>

/*
 @brief: TreeNode for Binary Search Tree
 */
struct BSTNode {
    int val;        // value
    BSTNode *p;     // pointer to parent
    BSTNode *left;  // pointer to left child
    BSTNode *right; // pointer to right child
    BSTNode(int v) : val(v), p(nullptr), left(nullptr), right(nullptr) {  }
};

/*
 Binary search tree class
 
 Traversal:
 for inorder traversal the root is visited twice, once when root is first reached, once when the left subtree has been visited, so it is critical to identify these two cases, otherwise infinite loop may occur. When using stack, when a node is poped out of the stack, its left subtree has been visited; When using morris, if the predecessor points to the current root, left subtree of current root has been visited.

 */
class BST {
public:
    BST() : root(nullptr) {  }
    // parameter random denotes whether to shuffle the input before BST is constructed
    BST(std::vector<int> node_list, bool random = false);
    ~BST();
    bool empty() { return root == nullptr; }
    BSTNode *search(int target);
    BSTNode *successor(BSTNode *curr);
    BSTNode *predecessor(BSTNode *curr);
    BSTNode *minimum(BSTNode *curr);    // TODO make curr default to root
    BSTNode *maximum(BSTNode *curr);    // TODO make curr default to root
    
    // recursive traversal
    void inorder_traversal_recursive();
    void preorder_traversal_recursive();
    void postorder_traversal_recursive();
    // morris is applicable when the tree is not read only, time is O(n) since each node is visited at most twice (three times?), space is O(1)
    void inorder_traversal_morris();
    void preorder_traversal_morris();
    // using stack time O(n) space O(h) worse case O(n)
    void inorder_traversal_stack();

    void insert_node(int value);
    void delete_node(BSTNode *targetNode);
private:
    void inorder_traversal_recursive_helper(BSTNode *curr);
    void preorder_traversal_recursive_helper(BSTNode *curr);
    void postorder_traversal_recursive_helper(BSTNode *curr);
    void transplant(BSTNode *u, BSTNode *v);
    void destruct_helper(BSTNode *curr);
    BSTNode *root;
};

#endif /* ibst_hpp */
