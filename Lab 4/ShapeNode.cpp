//
//  ShapeNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeNode class below

#include "Shape.h"
#include "ShapeNode.h"
#include <iostream>
#include <string>

/* Make constructor: */
ShapeNode::ShapeNode(){
    myShape = NULL;
    next = NULL;
}

/* Make destructor: */
ShapeNode::~ShapeNode(){
    delete myShape;

    next = NULL;
    myShape = NULL;
}

/* Accessors: */
Shape* ShapeNode::getShape() const{
    return myShape;
}

ShapeNode* ShapeNode::getNext() const{
    return next;
}   // returns next

/* Mutators: */
void ShapeNode::setShape(Shape* ptr){
    myShape = ptr;
}

void ShapeNode::setNext(ShapeNode* ptr){
    next = ptr;
}

void ShapeNode::print() const{
    (myShape -> draw());
}
