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
    BSTNode *current = root;
    while(current != nullptr) {
        // when current has no left child, visited current and switch to right child
        if(current->left  == nullptr) {
            cout << current->val << " ";
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
                cout << current->val << " ";
                current = current->right;
            }
        }
    }
    cout << endl;
}

void BST::inorder_traversal_recursive() {
    inorder_traversal_recursive_helper(root);
    cout << endl;
}
void BST::inorder_traversal_recursive_helper(BSTNode *curr) {
    if(curr != nullptr) {
        inorder_traversal_recursive_helper(curr->left);
        cout << curr->val << " ";
        inorder_traversal_recursive_helper(curr->right);
    }
}

void BST::inorder_traversal_stack() {
    BSTNode *current = root;
    stack<BSTNode *> stk;
    while(!stk.empty() || current != nullptr) {
        while(current != nullptr) {
            stk.push(current);
            current = current->left;
        }
        current = stk.top();
        stk.pop();
        cout << current->val << " ";
        current = current->right;
    }
    cout << endl;
}
void BST::preorder_traversal_morris() {
    BSTNode *current = root;
    while(current != nullptr) {
        if(current->left == nullptr) {
            cout << current->val << " ";
            current = current->right;
        } else {
            BSTNode *predec = current->left;
            while(predec->right != nullptr && predec->right != current)
                predec = predec->right;
            if(predec->right == nullptr) {
                cout << current->val << " ";
                predec->right = current;
                current = current->left;
            } else {
                predec->right = nullptr;
                current = current->right;
            }
        }
    }
    cout << endl;
}

void BST::preorder_traversal_recursive() {
    preorder_traversal_recursive_helper(root);
    cout << endl;
}
void BST::preorder_traversal_recursive_helper(BSTNode *curr) {
    if(curr != nullptr) {
        cout << curr->val << " ";
        preorder_traversal_recursive_helper(curr->left);
        preorder_traversal_recursive_helper(curr->right);
    }
}
void BST::postorder_traversal_recursive() {
    postorder_traversal_recursive_helper(root);
    cout << endl;
}
void BST::postorder_traversal_recursive_helper(BSTNode *curr) {
    if(curr != nullptr) {
        postorder_traversal_recursive_helper(curr->left);
        postorder_traversal_recursive_helper(curr->right);
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
