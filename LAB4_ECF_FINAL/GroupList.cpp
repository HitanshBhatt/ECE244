//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below

#include "GroupList.h"
#include "ShapeList.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"

#include <iostream>
#include <string>

/* Constructor: sets head to nullptr */
GroupList::GroupList(){
    head = NULL;
}

/* Destructor: deletes all list nodes, including all the ShapeList attached to each GroupNode*/
GroupList::~GroupList(){
    GroupNode* pointer = head;                             //make sure to delete later using "delete"
    GroupNode* temp_pointer = NULL;

    while(pointer != NULL){                            //while head is not pointing to a null space in memory
        temp_pointer = pointer -> getNext();                             //setting the next node as the current node
        delete pointer;
        pointer = temp_pointer;
        //head = pointer -> getNext();                //look at the next node
        //delete pointer;                             //pointer deleted, should cause NO memory leaks
    }

    //pointer = NULL;                                 //always set pointer to NULL after deleting
}

/* Accessor: returns the head pointer */
GroupNode* GroupList::getHead() const{
    return head;
}

/* Mutator: sets the head pointer to ptr */
void GroupList::setHead(GroupNode* ptr){
    head = ptr;
}

/* inserts the node pointed to by s at the end of the list */
void GroupList::insert(GroupNode* s){
    GroupNode* pointer = head;
	s->setNext(NULL);
	if (head == NULL) {
		head = s;
		return;
	}
	while (pointer->getNext() != nullptr){
            pointer = pointer->getNext();
        }
	pointer->setNext(s);
}

/* removes the group with the name "name" from the list and returns a pointer to the removed GroupNode returns nullptr is name is not found on list*/
GroupNode* GroupList::remove(string name){
    GroupNode* remove_ptr = head;
	GroupNode* prev = NULL;

	if (remove_ptr != NULL && remove_ptr->getName() == name) {
		head = remove_ptr->getNext();
		return remove_ptr;
	} else {
		while (remove_ptr != NULL && remove_ptr->getName() != name) {
			prev = remove_ptr;
			remove_ptr = remove_ptr->getNext();
		}
		if (remove_ptr == NULL) return NULL;
		prev->setNext(remove_ptr->getNext());
	}
	return remove_ptr;

}

/* prints the list, one GroupNode at a time */
void GroupList::print() const{
    GroupNode* pointer = head;

    while (pointer != NULL){
        pointer -> print();
        pointer = pointer -> getNext();
    }
    
}