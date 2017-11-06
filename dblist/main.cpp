//
//  main.cpp
//  dblist
//
//  Created by Colin on 27/09/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include <iostream>
#include "dblist.hpp"

int main(int argc, const char * argv[]) {
    dbList dblst;
    for(int i = 0; i != 11; ++i) {
        dblst.insert_node(i);
    }
    dblst.print();
    dblst.print_reverse();
    dblst.delete_node(dblst.search(5));
    dblst.print();
    return 0;
}
