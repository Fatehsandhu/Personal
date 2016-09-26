//
//  dlisttester.cpp
//  BTP_Lab3
//
//  Created by Fateh Sandhu on 2016-09-23.
//  Copyright © 2016 Fateh Sandhu. All rights reserved.
//
#include "slist.h"
#include <iostream>
int main(void){
    SList<int> list;
    list.push_front(10);
    list.push_front(5);
    list.push_front(15);
    list.push_back(43);
    list.print();
    cout << "***********" << endl;
    list.pop_back();
    list.pop_front();
    list.print();
}
