//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below

#include "ShapeList.h"
#include "Shape.h"
#include "ShapeNode.h"

#include <iostream>
#include <string>

/* Constructor: sets head to nullptr*/
ShapeList::ShapeList(){
    head = NULL;
}

/* deletes all list nodes starting with head plus associated Shapes*/
ShapeList::~ShapeList(){
    ShapeNode* pointer;

    while(head != NULL){
        pointer = head;
        head = (pointer -> getNext());
        delete pointer;
    }

    pointer = NULL;
}

/* Accessor: returns the head pointer */
ShapeNode* ShapeList::getHead() const{
    return head;
}

/* Mutator: sets the head pointer to ptr */
void ShapeList::setHead(ShapeNode* ptr){
    head = ptr;
}

/* finds a shape node with the specified shape name returns a pointer to the node if found, otherwise returns nullptr if the node is not found */
ShapeNode* ShapeList::find(string name) const{
    ShapeNode* pointer = head;

    while(pointer != NULL){
        if ((pointer -> getShape() -> getName()) == name){
            return pointer;
        }
        else{
            pointer = (pointer -> getNext());
        }
    }

    return NULL;
}

/* inserts the node pointed to by s at the end of the list; s should never be nullptr */
void ShapeList::insert(ShapeNode* s){
    if (head != NULL){
        ShapeNode* pointer = head;
        while ((pointer -> getNext()) != NULL){                 //iterate until the end of the list
            pointer = pointer -> getNext();
        }

        pointer -> setNext(s);          //add to the end of the list
    }
    else if (head == NULL){
        head = s;
    }
}

/* removes the node with the shape called name returns a pointer to the removed node or nullptr is a node with name does not exist*/
ShapeNode* ShapeList::remove(string name){
    ShapeNode* prev = NULL;
    ShapeNode* cur = head;
    ShapeNode* next;

    while(cur != NULL){             //while cur doesn't point to a NULL space in memory
        next = cur -> getNext();

        if ((cur -> getShape() -> getName()) == name){
            if (prev = NULL){
                head = next;
            }
            else{
                prev -> setNext(next);
            }

            cur -> setNext(NULL);
            return cur;
        }
        else{
            prev = cur;
            cur = next;
            if (next != NULL) {
                next = next = (next -> getNext());
            }
            else{
                next = NULL;
            }
        }
    }

    return NULL;
}

/* prints the list */
void ShapeList::print() const{
    ShapeNode* pointer = head;

    while (pointer != NULL){
        pointer -> print();
        pointer = pointer -> getNext();
    }
    
}