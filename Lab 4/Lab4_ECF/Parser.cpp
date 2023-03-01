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

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
enum commandCode {shapeIO, groupIO, drawIO, moveIO, deleteIO};
commandCode passCode(string input) {
    if (input == "shape") return shapeIO;
    if (input == "group") return groupIO;
    if (input == "draw") return drawIO;
    if (input == "move") return moveIO;
    if (input == "delete") return deleteIO;
}

string tempName, tempType, tempOldGroup, tempNewGroup; int tempXLoc, tempYLoc, tempXSize, tempYSize;
int errorPriority = 0;
int c1, c2;
bool invalidArgument, invalidName, invalidType, invalidLocation, invalidSize;

void invalidNameErrorCase(string input) {
    c1 = 0;
    for (int i = 0; i < 6; ++i) {
        if (keyWordsList[i] == input) {c1 += 1; invalidName = false;}
    } //check if tempName is a keyword
    if (c1 != 0) {
        invalidName = true; 
        if (errorPriority >= 1) {errorPriority = 1;}
    } //if tempName matches with a keyword, then it is an invalid name, and if error priority is not lower than 3, set it to 3
    for (int i = 0; i < 3; ++i) {
        if (shapeTypesList[i] == input) {c1 += 1; invalidName = false;}
    } //check if tempName is a shape type
    if (c1 != 0) {
        invalidName = true; 
        if ((errorPriority == 0) || (errorPriority >= 1)) {errorPriority = 1;};
    } //if tempName matches with a shape type, then it is an invalid name, and if error priority is not lower than 3, set it to 3
    c1 = 0; //reset counter
}

GroupNode* shapeNameIndex(string input1, GroupList* input2) {
    GroupNode* tptr = input2->getHead();
    while (tptr != NULL) {
        if (tptr->getShapeList()->find(input1) != NULL) {return tptr;}
        tptr = tptr->getNext();
    }
    return tptr;
}

GroupNode* groupNameIndex(string input1, GroupList* input2) {
    GroupNode* tptr = input2->getHead();
    while (tptr != NULL) {
        if (tptr->getName() == input1) {return tptr;}
        tptr = tptr->getNext();
    }
    return tptr;
}

bool shapeNameFound(string input1, GroupList* input2) {
    if (shapeNameIndex(input1, input2) != NULL) {
        return true;
    }
    else {return false;}
}

bool groupNameFound(string input1, GroupList* input2) {
    if (groupNameIndex(input1, input2) != NULL) {
        return true;
    }
    else {return false;}
}

bool nameAlreadyExistsErrorCase(string input1, GroupList* input2) {
    if (shapeNameFound(input1, input2) || groupNameFound(input1, input2)) {return true;}
    else {return false;}
}

void printError(int errorPriority) {
    switch (errorPriority) {
        case 1: 
            cout << "error: invalid name" << endl;
            cin.clear();
            break;
        case 2: 
            cout << "error: name " << tempName << " exists" << endl;
            cin.clear();
            break;
        case 3:
            cout << "error: shape " << tempName << " not found" << endl;
            cin.clear();
            break;
        case 4:
            cout << "error: group " << tempNewGroup << " not found" << endl;
            cin.clear();
            break;
        default:
            errorPriority = 0;
            break;
    }
    return;
}

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the poo group and add it to the group list
    //GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
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
        
        //reset all boolean flags
        errorPriority = 0;
        invalidName = false;

        if (errorPriority != 0) {lineStream.ignore(1000, '/n');}

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if ((command == " ") || command.empty()) {break;}

        if (command == "draw") {
            cout << "drawing: " << endl;
            gList->print();
        }

        if (!lineStream.eof()) {
            
            if (command == "draw") {
                cout << "hi" << endl;
            }
            switch (passCode(command)) {
                case shapeIO:
                    
                    lineStream >> tempName;
                    invalidNameErrorCase(tempName); //ERROR CASE 3: INVALID NAME
                    if (nameAlreadyExistsErrorCase(tempName, gList)) {
                        if ((errorPriority == 0) || (errorPriority >= 2)) {errorPriority = 2;}
                    }; //ERROR CASE 4: NAME ALREADY EXISTS
                    printError(errorPriority); if (errorPriority != 0) {break;} 
                    
                    lineStream >> tempType;
                    lineStream >> tempXLoc;
                    lineStream >> tempYLoc;
                    lineStream >> tempXSize;
                    lineStream >> tempYSize;
                    
                    if (errorPriority == 0) {
                        ShapeNode* shapeNodeInsert = new ShapeNode();
                        Shape* newShape = new Shape(tempName, tempType, tempXLoc, tempXSize, tempYLoc, tempYSize);
                        shapeNodeInsert->setShape(newShape);
                        poolGroup->getShapeList()->insert(shapeNodeInsert);
                        cout << tempName << ": " << tempType << " " << tempXLoc << " " << tempYLoc << " " << tempXSize << " " << tempYSize << endl;
                    }
                    break;

                case groupIO:
                    lineStream >> tempName;
                    invalidNameErrorCase(tempName); //ERROR CASE 1: INVALID NAME
                    if (nameAlreadyExistsErrorCase(tempName, gList)) {
                        if ((errorPriority == 0) || (errorPriority >= 2)) {errorPriority = 2;}
                    }; //ERROR CASE 2: NAME ALREADY EXISTS
                    printError(errorPriority); if (errorPriority != 0) {break;} 

                    if (errorPriority == 0) {
                        GroupNode* newGroupNode = new GroupNode(tempName);
                        gList->insert(newGroupNode);
                        cout << tempName << ": group" << endl;
                    }
                    
                    break;

                case drawIO:
                    cout << "drawing: " << endl;
                    gList->print();
                    break;


                case moveIO: //FIGURE OUT
                    lineStream >> tempName;
                    invalidNameErrorCase(tempName); //ERROR CASE 1: INVALID NAME
                    if (!shapeNameFound(tempName, gList)) { //CHECK IF SHAPE OR GROUP NAME HERE
                        if ((errorPriority == 0) || (errorPriority >= 3)) {errorPriority = 3;}
                    } //ERROR CASE 3: shape name NOT FOUND
                    printError(errorPriority); if (errorPriority != 0) {break;}

                    lineStream >> tempNewGroup;
                    if (!groupNameFound(tempNewGroup, gList)) {
                        if ((errorPriority == 0) || (errorPriority >= 4)) {errorPriority = 4;}
                    } //error case 4: group name not found
                    printError(errorPriority); if (errorPriority != 0) {break;}

                    if (errorPriority == 0) {
                        GroupNode* OldGroup = shapeNameIndex(tempName, gList);
                        ShapeNode* temp = OldGroup->getShapeList()->remove(tempName);
                        temp->setNext(NULL);
                        GroupNode* temp2 = groupNameIndex(tempNewGroup, gList);
                        temp2->getShapeList()->insert(temp);

                        cout << "moved " << tempName << " to " << tempNewGroup << endl;

                    }
                    break;

                
                case deleteIO:
                    bool deleteShape = false;
                    bool deleteGroup = false;
                    lineStream >> tempName;
                    invalidNameErrorCase(tempName); //ERROR CASE 3: INVALID NAME
                    
                    if (!shapeNameFound(tempName, gList)) {
                        if ((errorPriority == 0) || (errorPriority >= 3)) {errorPriority = 3;}
                        if (groupNameFound(tempName,gList)) {
                            errorPriority = 0;
                        }
                    }
                    if (!groupNameFound(tempName, gList)) {
                        if ((errorPriority == 0) || (errorPriority >= 4)) {errorPriority = 4;}
                        if (!shapeNameFound(tempName, gList)) {
                            tempNewGroup = tempName;
                        }
                        if (shapeNameFound(tempName,gList)) {
                            errorPriority = 0;
                        }
                    } //ERROR CASE 5: NAME NOT FOUND
                    if (tempName == "pool") {
                        cout << "error: invalid name" << endl;
                        break;
                    }
                    printError(errorPriority); if (errorPriority != 0) {break;}
                    
                    ShapeNode* tempShape;
                    GroupNode* tempGroup;

                    if (shapeNameIndex(tempName, gList) != NULL) {
                        deleteShape = true;
                        tempGroup = shapeNameIndex(tempName, gList);
                        tempShape = tempGroup->getShapeList()->find(tempName);
                        
                    }
                    if (groupNameIndex(tempName, gList) != NULL) {
                        deleteGroup = true;
                        tempGroup = groupNameIndex(tempName, gList);
                    }
                    if (errorPriority == 0) {
                        if (deleteShape) {
                            tempGroup->getShapeList()->remove(tempName);
                            delete tempShape;
                            cout << tempName << ": deleted" << endl;
                        }

                        if (deleteGroup) {
                            GroupNode* tempGroup = gList->remove(tempName);
                            ShapeNode* tempShape = tempGroup->getShapeList()->getHead();
                           
                            gList->getHead()->getShapeList()->insert(tempShape);
                            tempGroup->getShapeList()->setHead(NULL);
                            delete tempGroup;
                            cout << tempName << ": deleted" << endl;
                        }
                    }
                    break;
            }        
        }
        cin.clear();

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}