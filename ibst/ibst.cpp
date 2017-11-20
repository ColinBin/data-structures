//
//  ibst.cpp
//  ibst
//
//  Created by Colin on 05/11/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include "ibst.hpp"
#include <algorithm>
#include <stack>

using std::vector; using std::stack;
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
void BST::inorder_traversal_morris() {
    vector<BSTNode *> res;
    BSTNode *current = root;
    while(current != nullptr) {
        // when current has no left child, visited current and switch to right child
        if(current->left  == nullptr) {
            res.push_back(current);
            current = current->right;
        } else {
            // when left child is no nullptr, find predecessor
            BSTNode *predec = current->left;
            while(predec->right != current && predec->right != nullptr)
                predec = predec->right;
            // the left subtree of current has not been visited
            if(predec->right == nullptr) {
                predec->right = current;
                current = current->left;
            } else {
                // left subtree has been visited, reset pointer and visit current
                predec->right = nullptr;
                res.push_back(current);
                current = current->right;
            }
        }
    }
    print_traversal_result(res);
}

void BST::inorder_traversal_recursive() {
    vector<BSTNode *> res;
    inorder_traversal_recursive_helper(root, res);
    print_traversal_result(res);
}
void BST::inorder_traversal_recursive_helper(BSTNode *curr, vector<BSTNode *> &res) {
    if(curr != nullptr) {
        inorder_traversal_recursive_helper(curr->left, res);
        res.push_back(curr);
        inorder_traversal_recursive_helper(curr->right, res);
    }
}

void BST::inorder_traversal_stack() {
    vector<BSTNode *> res;
    BSTNode *current = root;
    stack<BSTNode *> stk;
    while(!stk.empty() || current != nullptr) {
        while(current != nullptr) {
            stk.push(current);
            current = current->left;
        }
        current = stk.top();
        stk.pop();
        res.push_back(current);
        current = current->right;
    }
    print_traversal_result(res);
}
void BST::preorder_traversal_morris() {
    vector<BSTNode *> res;
    BSTNode *current = root;
    while(current != nullptr) {
        if(current->left == nullptr) {
            res.push_back(current);
            current = current->right;
        } else {
            BSTNode *predec = current->left;
            while(predec->right != nullptr && predec->right != current)
                predec = predec->right;
            if(predec->right == nullptr) {
                res.push_back(current);
                predec->right = current;
                current = current->left;
            } else {
                predec->right = nullptr;
                current = current->right;
            }
        }
    }
    print_traversal_result(res);
}
// very similar to the stack structure in recursive algorithm
void BST::preorder_traversal_stack() {
    vector<BSTNode *> res;
    if(root == nullptr)
        return;
    stack<BSTNode *> stk;
    stk.push(root);
    while(!stk.empty()) {
        BSTNode *current = stk.top();
        stk.pop();
        res.push_back(current);
        if(current->right != nullptr)
            stk.push(current->right);
        if(current->left != nullptr)
            stk.push(current->left);
    }
    print_traversal_result(res);
}

void BST::preorder_traversal_recursive() {
    vector<BSTNode *> res;
    preorder_traversal_recursive_helper(root, res);
    print_traversal_result(res);
}
void BST::preorder_traversal_recursive_helper(BSTNode *curr, vector<BSTNode *> &res) {
    if(curr != nullptr) {
        res.push_back(curr);
        preorder_traversal_recursive_helper(curr->left, res);
        preorder_traversal_recursive_helper(curr->right, res);
    }
}

// the result will be in stk2, which takes theta(n) space
void BST::postorder_traversal_two_stacks() {
    vector<BSTNode *> res;
    if(empty())
        return;
    stack<BSTNode *> stk1, stk2;
    stk1.push(root);
    while(!stk1.empty()) {
        BSTNode *curr = stk1.top();
        stk1.pop();
        stk2.push(curr);
        if(curr->left != nullptr)
            stk1.push(curr->left);
        if(curr->right != nullptr) {
            stk1.push(curr->right);
        }
    }
    while(!stk2.empty()) {
        res.push_back(stk2.top());
        stk2.pop();
    }
    print_traversal_result(res);
}

// can also used to find the maximum height of a binary tree
void BST::postorder_traversal_one_stack() {
    vector<BSTNode *> res;
    stack<BSTNode *> stk;
    BSTNode *current = root;
    while(!stk.empty() || current != nullptr) {
        if(current != nullptr) {
            stk.push(current);
            current = current->left;
        } else {
            BSTNode *temp = stk.top()->right;
            if(temp != nullptr)
                current = temp;
            else {
                temp = stk.top();
                stk.pop();
                res.push_back(temp);
                while(!stk.empty() && temp == stk.top()->right) {
                    temp = stk.top();
                    stk.pop();
                    res.push_back(temp);
                }
            }
        }
    }
    print_traversal_result(res);
}

void BST::postorder_traversal_recursive() {
    vector<BSTNode *> res;
    postorder_traversal_recursive_helper(root, res);
    print_traversal_result(res);
}
void BST::postorder_traversal_recursive_helper(BSTNode *curr, vector<BSTNode *> &res) {
    if(curr != nullptr) {
        postorder_traversal_recursive_helper(curr->left, res);
        postorder_traversal_recursive_helper(curr->right, res);
        res.push_back(curr);
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

void BST::print_traversal_result(const vector<BSTNode *> res) {
    for(const BSTNode *curr : res) {
        cout << curr->val << " ";
    }
    cout << endl;
}
