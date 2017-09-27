//
//  main.cpp
//  iqueue
//
//  Created by Colin on 27/09/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include <iostream>
#include "iqueue.hpp"
#include <stdexcept>
using std::cout; using std::cin; using std::endl;
using std::exception;
int main(int argc, const char * argv[]) {
    iQueue ique(10);
    // enque 9 eles and two overflows
    for(int i = 0; i != 11; ++i) {
        try {
            ique.enque(i);
        } catch(exception &err) {
            cout << err.what() << endl;
        }
    }
    // deque 5 eles
    for(int i = 0; i != 5; ++i) {
        try{
            cout << ique.deque() << endl;
        } catch(exception &err) {
            cout << err.what() << endl;
        }
    }
    // enque 5 eles
    for(int i = 0; i != 5; ++i) {
        try {
            ique.enque(i);
        } catch(exception &err) {
            cout << err.what() << endl;
        }
    }
    // deque 9 eles and two underflows
    for(int i = 0; i != 11; ++i) {
        try{
            cout << ique.deque() << endl;
        } catch(exception &err) {
            cout << err.what() << endl;
        }
    }
    return 0;
}
