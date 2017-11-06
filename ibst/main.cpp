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

int main(int argc, const char * argv[]) {
    vector<int> node_list = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    BST bst(node_list);
    bst.inorder_tree_walk();
    return 0;
}
