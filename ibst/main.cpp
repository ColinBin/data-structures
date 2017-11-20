//
//  main.cpp
//  ibst
//
//  Created by Colin on 05/11/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include <iostream>
#include "ibst.hpp"
#include <vector>

using std::cout; using std::endl;
using std::vector;

void test_preorder(BST &bst);
void test_inorder(BST &bst);
void test_postorder(BST &bst);

int main(int argc, const char * argv[]) {
    vector<int> node_list = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    BST bst(node_list);
    test_preorder(bst);
    test_inorder(bst);
    test_postorder(bst);
    return 0;
}

void test_inorder(BST &bst) {
    cout << "Inorder Traversal:" << endl;
    bst.inorder_traversal_recursive();
    bst.inorder_traversal_stack();
    bst.inorder_traversal_morris();
    cout << endl;
}
void test_preorder(BST &bst) {
    cout << "Preorder Traversal:" << endl;
    bst.preorder_traversal_recursive();
    bst.preorder_traversal_stack();
    bst.preorder_traversal_morris();
    cout << endl;
}
void test_postorder(BST &bst) {
    cout << "Postorder Traversal:" << endl;
    bst.postorder_traversal_recursive();
    bst.postorder_traversal_one_stack();
    bst.postorder_traversal_two_stacks();
    cout << endl;
}
