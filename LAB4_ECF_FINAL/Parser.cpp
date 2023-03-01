//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;
//string name;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void invalid_name();
void name_exists(string nameOfShape);
void shape_name_not_found(string nameofShape);
void group_name_not_found(string nameofGroup);

bool check_name(string name);
GroupNode* search_name(string name);
bool check_name_exists(string name);
GroupNode* search_group(string name);
bool check_group_exists(string name);
//string trim (const string& line);

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the poo group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while (!cin.eof()) {
        
        int x_location, x_size, y_location, y_size;
        string name, type, group;
        
        //line = trim(line);
        
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if (command == keyWordsList[0]) {
            //shape
            lineStream >> name;
            if (!check_name(name)){
                invalid_name(); 
                //goto jmp;
            }
            if (check_name_exists(name) || check_group_exists(name)){
                name_exists(name); 
                // /goto jmp;
            }
            lineStream >> type;
            lineStream >> x_location;
            lineStream >> y_location;
            lineStream >> x_size;
            lineStream >> y_size;

            Shape* new_shape = new Shape(name, type, x_location, x_size, y_location, y_size);
            ShapeNode* new_ShapeNode = new ShapeNode();
            new_ShapeNode->setShape(new_shape);
            new_ShapeNode->getShape()->draw();
            poolGroup->getShapeList()->insert(new_ShapeNode);

        } else if (command == keyWordsList[1]) {
            //group
            lineStream >> name;

            if (!check_name(name)){
                invalid_name();
                // goto jmp;
            }

            GroupNode* new_group_node = new GroupNode(name);
            gList->insert(new_group_node);
            cout << name << ": group" << endl;

        } else if (command == keyWordsList[2]) {
            //move
            lineStream >> name;

            if (check_name_exists(name)) {

                lineStream >> group;

                if (check_group_exists(group)) {
                    GroupNode* shapeMove = search_name(name);
                    GroupNode* newGroup = search_group(group);
                    newGroup->getShapeList()->insert(shapeMove->getShapeList()->remove(name));
                    cout << "moved " << name << " to " << group << endl;
                } else {
                    group_name_not_found(group);
                    //goto jmp;
                }
            } 
            else{
                shape_name_not_found(name);
                //goto jmp;
            } 

        } else if (command == keyWordsList[3]) {
            //delete
            lineStream >> name;

            if (!check_name(name)){
                invalid_name(); 
                //goto jmp;
            }

            if (check_name_exists(name)) {

                GroupNode* perform_delete = search_name(name);
                if (perform_delete != NULL) {

                    delete perform_delete->getShapeList()->remove(name);
                    cout << name << ": deleted" << endl;

                } 
                else{
                    shape_name_not_found(name);
                    //goto jmp;
                }
            } 
            else if (check_group_exists(name)){
                
                GroupNode* delete_group = search_group(name);

                if (delete_group != NULL){
                    while (delete_group->getShapeList()->getHead() != NULL){
                        string count_shape = (delete_group->getShapeList()->getHead()->getShape()->getName());
                        ShapeNode* node_count_shape = (delete_group->getShapeList()->remove(count_shape));
                        poolGroup->getShapeList()->insert(node_count_shape);
                    }

                    delete gList->remove(name);
                    cout << name << ": deleted" << endl;
                }
            }
            else{
                shape_name_not_found(name);
                //goto jmp;
            }
        }
        else if (command == keyWordsList[4]) {
            //draw
            cout << "drawing: " << endl;
            gList->print();
        }
        else{
            cout << "error: invalid command" << endl;
            //goto jmp;
        }

        cout << "> ";          // Prompt for input
        getline(cin, line);
    }  // End input loop until EOF.
    
    return 0;
}

/*string trim(const string& line) {
    const char* WhiteSpace = " \t\v\r\n";
    size_t start = line.find_first_not_of(WhiteSpace);
    size_t end = line.find_last_not_of(WhiteSpace);
    return start == end ? string() : line.substr(start, end - start + 1);
}*/

void invalid_name(){
    cout << "Error: invalid name" << endl;
}

void name_exists(string nameofShape){
    cout << "Error: name " << nameofShape << " exists" << endl;
}

void shape_name_not_found(string nameofShape){
    cout << "Error: shape " << nameofShape << " not found" << endl;
}

void group_name_not_found(string nameofGroup){
    cout << "Error: group " << nameofGroup << " not found" << endl;   
}

bool check_name(string name) {
    for (int i = 0; i < NUM_KEYWORDS; i++){
        if (name == keyWordsList[i]){
            return false;
        } 
    }

    for (int j = 0; j < NUM_TYPES; j++){
        if (name == shapeTypesList[j]){
            return false;
        } 
    }
    return true;
}

GroupNode* search_name(string name) {
    GroupNode* head = gList->getHead();

    while (head != NULL){

        if (head->getShapeList()->find(name) != NULL){
            return head;
        }

        head = (head->getNext());
    }

    return NULL;
}

bool check_name_exists(string name){
    GroupNode* head = gList->getHead();

    while (head != NULL){
        ShapeList* traverse = head->getShapeList();

        if(traverse != NULL){
            if(traverse -> find(name) != NULL){
                return true;
            }
        }
        /*if(head->getShapeList()->find(name) != NULL){
            return true;
        } 
        head = (head->getNext());*/
    }
    return false;
}

GroupNode* search_group(string name) {
    GroupNode* head = gList->getHead();

    while (head != NULL){
        if (head->getName() == name){
            return head;
        }

        head = (head->getNext());
    }

    return NULL;
}

bool check_group_exists(string name) {
    GroupNode* head = gList->getHead();

    while (head != NULL){

        if (head->getName() == name){
            return true;
        }

        head = (head->getNext());
    }
    return false;
}