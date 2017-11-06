//
//  main.cpp
//  slist
//
//  Created by Colin on 27/09/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include <iostream>
#include "slist.hpp"

int main(int argc, const char * argv[]) {
    sList slist;
    for(int i = 0; i != 11; ++i) {
        slist.insert_node(i);
    }
    slist.print();
    slist.delete_node(slist.search_prev(5));
    slist.print();
    slist.delete_node(slist.search_prev(8));
    slist.print();
    return 0;
}
