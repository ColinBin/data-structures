//
//  main.cpp
//  istack
//
//  Created by Colin on 27/09/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include "istack.hpp"

using std::cout; using std::cin; using std::endl;
using std::exception;
int main() {
    iStack istk(10);
    for(int i = 0; i < 11; ++i) {
        try {
            istk.push(i);
        } catch(exception &err) {
            cout << err.what() << endl;
        }
    }
    for(int i = 0; i < 11; ++i) {
        try{
            cout << istk.pop() << endl;
        } catch(exception &err) {
            cout << err.what() << endl;
        }
    }
    return 0;
}
