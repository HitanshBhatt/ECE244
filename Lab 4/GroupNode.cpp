//
//  GroupNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupNode class below

#include "GroupNode.h"
#include "Shape.h"
#include "ShapeList.h"
#include "ShapeNode.h"
#include <iostream>
#include <string>

/* Constructor: sets group name to n and makes myShapeList */
GroupNode::GroupNode(string n){
    name = n;
    myShapeList = new ShapeList();          //allocation memory, make sure to de-allocate
    next = NULL;                            //sets next to nullptr
}

/* Destructor: deletes the myShapeList list */
GroupNode::~GroupNode(){
    delete myShapeList;
    myShapeList = NULL;
    next = NULL;
}

/* Accessors: */
string GroupNode::getName() const{
    return name;
}            // returns group name
GroupNode* GroupNode::getNext() const{
    return next;
}        // returns next
ShapeList* GroupNode::getShapeList() const{
    return myShapeList;
}   // returns myShapeList

/* Mutators: */
void GroupNode::setShapeList(ShapeList *ptr){
    myShapeList = ptr;
} // sets myShapeList to ptr
void GroupNode::setNext(GroupNode *ptr){
    next = ptr;
}      // sets next to ptr

void GroupNode::print() const{
    cout << name << ":" << endl;
    (myShapeList -> print());
}                // prints the GroupNode
