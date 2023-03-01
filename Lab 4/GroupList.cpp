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
    GroupNode* pointer;                             //make sure to delete later using "delete"

    while(head != NULL){                            //while head is not pointing to a null space in memory
        pointer = head;                             //setting the next node as the current node
        head = pointer -> getNext();                //look at the next node
        delete pointer;                             //pointer deleted, should cause NO memory leaks
    }

    pointer = NULL;                                 //always set pointer to NULL after deleting
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
    if (head != NULL){
        GroupNode* pointer = head;
        while ((pointer -> getNext()) != NULL){                 //iterate until the end of the list
            pointer = pointer -> getNext();
        }

        pointer -> setNext(s);          //add to the end of the list
    }
    else if (head == NULL){
        head = s;
    }
}

/* removes the group with the name "name" from the list and returns a pointer to the removed GroupNode returns nullptr is name is not found on list*/
GroupNode* GroupList::remove(string name){
    GroupNode* prev = NULL;
    GroupNode* cur = head;
    GroupNode* next;

    while(cur != NULL){             //while cur doesn't point to a NULL space in memory
        next = cur -> getNext();

        if ((cur -> getName()) == name){
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

/* prints the list, one GroupNode at a time */
void GroupList::print() const{
    GroupNode* pointer = head;

    while (pointer != NULL){
        pointer -> print();
        pointer = pointer -> getNext();
    }
    
}