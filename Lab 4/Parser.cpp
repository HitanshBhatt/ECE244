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
string check_name_type(string name);

int main() {
    // Create the groups list
    gList = new GroupList();

    int x_location, x_size, y_location, y_size;
    string type; // nameExists;
    
    // Create the poo group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        if(command == keyWordsList[0]){
            lineStream >> command;

            /* !!!!!!!!ADD LINE HERE!!!!!!!! */
            string nameExists = check_name_type(command);

            if (nameExists == ""){
                lineStream >> type;
                lineStream >> x_location;
                lineStream >> y_location;
                lineStream >> x_size;
                lineStream >> y_size;

                Shape* new_shape = new Shape(command, type, x_location, y_location, x_size, y_size);
                ShapeNode* new_ShapeNode = new ShapeNode;
                new_ShapeNode -> setShape(new_shape);
                gList -> getHead() -> getShapeList() -> insert(new_ShapeNode);
                new_shape -> draw();
            }
            else{
                if (nameExists == "keyword"){
                    invalid_name();
                }
                else{
                    name_exists(command);
                }
            }
        }

        else if(command == keyWordsList[1]){
            lineStream >> command;

            string nameExists = check_name_type(command);

            if(nameExists == ""){
                GroupNode* new_group_node = new GroupNode(command);
                gList -> insert(new_group_node);
                cout << command << ": group" << endl;
            }
            else{
                if (nameExists == "keyword"){
                    invalid_name();
                }
                else{
                    name_exists(command);
                }
            }
        }

        else if (command == keyWordsList[2]){
            lineStream >> command;

            string nameExists = check_name_type(command);

            if (nameExists == "shape"){
                string name = command;
                lineStream >> command;
                string nameExists = check_name_type(command);

                if(nameExists == "group"){
                    string group = command;

                    GroupNode* iterate_group = (gList -> getHead());
                    bool found = false;

                    GroupNode* newGroup;
                    ShapeNode* shapeMove;

                    while (iterate_group != NULL){
                        if ((iterate_group -> getName()) == group){
                            newGroup = iterate_group;
                        }

                        ShapeList* shape_list = (iterate_group -> getShapeList());

                        if (shape_list != NULL & !found){
                            shapeMove = (shape_list -> remove(name));

                            if (shapeMove != NULL){
                                found = true;
                            }
                        }

                        iterate_group = (iterate_group -> getNext());
                    }

                    newGroup -> getShapeList() -> insert(shapeMove);

                    cout << "moved " << name << " to " << group << endl;
                }
            }
            else{
                if (nameExists == "keyword"){
                    invalid_name();
                }
                else{
                    shape_name_not_found(command);
                }
            }
        }

        else if (command == keyWordsList[3]){
            lineStream >> command;

            string nameExists = check_name_type(command);

            if (nameExists == "keyword"){
                invalid_name();
            }
            else if(nameExists == "group"){
                GroupNode* perform_delete = (gList -> remove(command));

                gList -> getHead() -> getShapeList() -> insert(perform_delete -> getShapeList() -> getHead());

                while((perform_delete -> getShapeList() -> getHead()) != NULL){
                    perform_delete -> getShapeList() -> setHead(perform_delete -> getShapeList() -> getHead() -> getNext());
                }

                delete perform_delete;
                perform_delete = NULL;

                cout << command << ": deleted" << endl;
            }
            else if (nameExists == "shape"){
                GroupNode* iterateGroup = (gList -> getHead());

                while (iterateGroup != NULL){
                    ShapeList* shape_list = (iterateGroup -> getShapeList());

                    if (shape_list != NULL){
                        ShapeNode* perform_delete = (shape_list -> remove(command));

                        if (perform_delete != NULL){
                            cout << (perform_delete -> getShape() -> getName()) << ": deleted" << endl;
                            delete perform_delete;
                        }
                    }

                    iterateGroup = (iterateGroup -> getNext());
                }
            }
            else if(nameExists == ""){
                shape_name_not_found(command);
            }
        }

        else if (command == keyWordsList[4]){
            cout << "drawing:" << endl;
            gList -> print();
        }
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

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

string check_name_type(string name){
    for (int i = 0; i < NUM_KEYWORDS; i++){
        if (name == keyWordsList[i]){
            return "keyword";
        }
    }

    for (int j = 0; j < NUM_TYPES; j++){
        if (name == shapeTypesList[j]){
            return "keyword";
        }
    }

    GroupNode* iterate_Group = (gList -> getHead());

    while (iterate_Group != NULL){
        if (name == (iterate_Group -> getName())){
            return "group";
        }
        else{
            ShapeList* list = (iterate_Group -> getShapeList());

            if (list != NULL){
                if ((list -> find(name)) != NULL){
                    return "shape";
                }
            }
        }
    }

    return "";
}

