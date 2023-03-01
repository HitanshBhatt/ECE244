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

/* Constructor: sets head to NULL*/
ShapeList::ShapeList(){
    head = NULL;
}

/* deletes all list nodes starting with head plus associated Shapes*/
ShapeList::~ShapeList(){
    ShapeNode* pointer = head;
    ShapeNode* temp_ptr = NULL;
    while (pointer != NULL) {
        temp_ptr = pointer->getNext();
	delete pointer;
	pointer = temp_ptr;
    }
}

/* Accessor: returns the head pointer */
ShapeNode* ShapeList::getHead() const{
    return head;
}

/* Mutator: sets the head pointer to ptr */
void ShapeList::setHead(ShapeNode* ptr){
    head = ptr;
}

/* finds a shape node with the specified shape name returns a pointer to the node if found, otherwise returns NULL if the node is not found */
ShapeNode* ShapeList::find(string name) const{
    ShapeNode* pointer = head;
	ShapeNode* prev = NULL;
	if (pointer == NULL) return NULL;
	while (pointer != NULL) {
		if (pointer->getShape()->getName() == name) return pointer;
		pointer = pointer->getNext();
	}
	return NULL;
}

/* inserts the node pointed to by s at the end of the list; s should never be NULL */
void ShapeList::insert(ShapeNode* s){
    s->setNext(NULL);
	if (head == NULL) head = s;
	else {
		ShapeNode* pointer = head;
		while (pointer->getNext() != NULL) pointer = pointer->getNext();
		pointer->setNext(s);
	}
}

/* removes the node with the shape called name returns a pointer to the removed node or NULL is a node with name does not exist*/
ShapeNode* ShapeList::remove(string name){
    ShapeNode* remove_ptr = head;
    ShapeNode* prev = NULL;
    if(remove_ptr == NULL) return NULL;
    while(remove_ptr != NULL) {
        if(remove_ptr->getShape()->getName()==name) break;
        prev = remove_ptr;
        remove_ptr = remove_ptr->getNext();
    }
    
    if(remove_ptr == head){
        head=head->getNext();
        return remove_ptr;
    }
    prev->setNext(remove_ptr->getNext());
    return remove_ptr; 
}

/* prints the list */
void ShapeList::print() const{
    ShapeNode* pointer = head;

    while (pointer != NULL){
        pointer -> print();
        pointer = pointer -> getNext();
    }
    
}