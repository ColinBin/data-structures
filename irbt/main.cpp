//
//  main.cpp
//  irbt
//
//  Created by Colin on 07/11/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include <iostream>
#include "irbt.hpp"
#include <vector>

using std::cout; using std::endl;
using std::vector;

int main(int argc, const char * argv[]) {
    vector<int> value_list = {11, 2, 14, 1, 7, 15, 5, 8};
    RBT rbt(value_list);
    rbt.inorder_tree_walk();
    cout << rbt.predecessor(rbt.search(5))->value << endl;
    return 0;
}
