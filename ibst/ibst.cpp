//
//  ibst.cpp
//  ibst
//
//  Created by Colin on 05/11/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include "ibst.hpp"
#include <algorithm>

using std::vector;
using std::cout; using std::endl;

BST::BST(vector<int> node_list, bool random) {
    if(random) {
        std::random_shuffle(node_list.begin(), node_list.end());
    }
    for(auto node_val : node_list) {
        insert_node(node_val);
    }
}
BST::~BST() {
    destruct_helper(root);
}
void BST::destruct_helper(BSTNode *curr) {
    if(curr != nullptr) {
        destruct_helper(curr->left);
        destruct_helper(curr->right);
        delete curr;
    }
}
void BST::insert_node(int value) {
    if(empty()) {
        root = new BSTNode(value);
    } else {
        BSTNode *dummy = root;
        while(true) {
            if(dummy->val > value) {
                if(dummy->left != nullptr)
                    dummy = dummy->left;
                else {
                    dummy->left = new BSTNode(value);
                    dummy->left->p = dummy;
                    break;
                }
            } else {
                if(dummy->right != nullptr)
                    dummy = dummy->right;
                else {
                    dummy->right = new BSTNode(value);
                    dummy->right->p = dummy;
                    break;
                }
            }
        }
    }
}
void BST::inorder_tree_walk() {
    inorder_tree_walk_helper(root);
    cout << endl;
}
void BST::inorder_tree_walk_helper(BSTNode *curr) {
    if(curr != nullptr) {
        inorder_tree_walk_helper(curr->left);
        cout << curr->val << " ";
        inorder_tree_walk_helper(curr->right);
    }
}
void BST::preorder_tree_walk() {
    preorder_tree_walk_helper(root);
    cout << endl;
}
void BST::preorder_tree_walk_helper(BSTNode *curr) {
    if(curr != nullptr) {
        cout << curr->val << " ";
        preorder_tree_walk_helper(curr->left);
        preorder_tree_walk_helper(curr->right);
    }
}
void BST::postorder_tree_walk() {
    postorder_tree_walk_helper(root);
    cout << endl;
}
void BST::postorder_tree_walk_helper(BSTNode *curr) {
    if(curr != nullptr) {
        postorder_tree_walk_helper(curr->left);
        postorder_tree_walk_helper(curr->right);
        cout << curr->val << " ";
    }
}
BSTNode *BST::minimum(BSTNode *curr) {
    if(curr == nullptr)
        return nullptr;
    while(curr->left != nullptr)
        curr = curr->left;
    return curr;
}
BSTNode *BST::maximum(BSTNode *curr) {
    if(curr == nullptr)
        return nullptr;
    while(curr->right != nullptr)
        curr = curr->right;
    return curr;
}
BSTNode *BST::successor(BSTNode *curr) {
    if(curr == nullptr)
        return nullptr;
    if(curr->right != nullptr)
        return minimum(curr->right);
    BSTNode *parent = curr->p;
    while(parent != nullptr && curr != parent->left) {
        curr = parent;
        parent = parent->p;
    }
    return parent;
}
BSTNode *BST::predecessor(BSTNode *curr) {
    if(curr == nullptr)
        return nullptr;
    if(curr->left != nullptr)
        return maximum(curr->left);
    BSTNode *parent = curr->p;
    while(parent != nullptr && curr != parent->right) {
        curr = parent;
        parent = parent->p;
    }
    return parent;
}

BSTNode *BST::search(int target) {
    BSTNode *dummy = root;
    while(dummy != nullptr) {
        if(dummy->val == target)
            break;
        else if(dummy->val > target)
            dummy = dummy->left;
        else
            dummy = dummy->right;
    }
    return dummy;
}
void BST::delete_node(BSTNode *targetNode) {
    if(targetNode == nullptr)
        return;
    if(targetNode->left == nullptr)
        transplant(targetNode, targetNode->right); // also deals with two null children
    else if(targetNode->right == nullptr)
        transplant(targetNode, targetNode->left);
    else {
        // successor takes its place
        BSTNode *succ = minimum(targetNode->right);
        if(succ != targetNode->right) {
            transplant(succ, succ->right);
            succ->right = targetNode->right;
            targetNode->right->p = succ;
        }
        transplant(targetNode, succ);
        succ->left = targetNode->left;
        targetNode->left->p = succ;
    }
    delete targetNode;
    return;
}
void BST::transplant(BSTNode *u, BSTNode *v) {
    if(u == nullptr)
        return;
    if(u->p == nullptr)
        root = v;
    else if(u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }
    if(v != nullptr)
        v->p = u->p;
}
