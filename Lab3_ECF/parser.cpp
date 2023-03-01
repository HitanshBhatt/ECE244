//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright ÃÂ© 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

/* Helper functions for errors: invalid {command, argument, shape name, shape name exists, shape name not found, shape type, value, too many arguments, too few arguments, shape array is full} ; no return type*/
void invalid_command();
void invalid_arg();
void invalid_shape_name();
void shape_name_exists(string nameOfShape);
void shape_name_not_found(string nameOfShape);
void invalid_shape_type();
void invalid_val();
void excess_arg();
void too_few_arg();
void sArray_full();

/*Algorithm helper functions*/
void del_array();
string errorResponse(int errorCode, string name);
Shape* shape_search(string name);

int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        //bool is_valid = false;

        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        //if linestream does not fail
        if(!lineStream.fail()) {
            if(command == "maxShapes") {
                int next_val;
                
                lineStream >> next_val;;

                if((!lineStream.fail()) && (lineStream.peek() == -1 || lineStream.peek() == 32)) {
                    string extra;

                    lineStream >> extra;

                    if(lineStream.eof() && lineStream.fail()) {
                        if(shapesArray != NULL) {
                            del_array();
                        }
                        //set max_shapes to the next value after deletion
                        max_shapes = next_val;
                        shapesArray = new Shape*[max_shapes];

                        cout << "New database: max shapes is " << max_shapes << endl;
                    }
                    else {
                        excess_arg();
                    }
                }
                else {
                    if (lineStream.eof()) { //if reached end of file, arguments are less than expected
                        too_few_arg(); 
                    }
                    else {      //if none of the above, then the argument has to be invalid
                        invalid_arg();
                    }
                }
            }

            else if (command == "create") {
                string name;

                lineStream >> name;

                if (!lineStream.fail()) {
                    bool name_exists = false;           //bool variable to check if the name already exists, false by default
                    for (int i = 0; i < shapeCount; i++) {
                        if (shapesArray != NULL) {
                            if (shapesArray[i] != NULL) {
                                if (name == (shapesArray[i])->getName()) {        //check if name is already present in shapesArray
                                    name_exists = true;                           //set name_exists to true since name exists
                                    shape_name_exists(name);                      //print error message
                                    break;
                                }
                            }
                        }
                    }

                    for (int i = 0; i < NUM_KEYWORDS; i++) {                       //check the list of key words
                        if (name == keyWordsList[i]) {
                            name_exists = true;
                            invalid_shape_name();
                            break;
                        }
                    }
                    
                    for (int i = 0; i < NUM_TYPES; i++) {                           //check the list of shape types
                        if (name == shapeTypesList[i]) {
                            name_exists = true;
                           invalid_shape_name();
                            break;
                        }
                    }
                    
                    if (!name_exists) {                                             //if name_exists is not true, i.e, if name does not exist
                        string type;

                        lineStream >> type;

                        if (!lineStream.fail()) {
                            bool shape_exists = false;                              //bool variable to check if shape already exists

                            for (int i = 0; i < NUM_TYPES; i++) {
                                if (type == shapeTypesList[i]){
                                    shape_exists = true;
                                    break;
                                }
                            }

                            if (shape_exists) {
                                int x_location, y_location, x_size, y_size;
                                string n;

                                lineStream >> x_location;

                                if (!lineStream.fail() && (x_location >= 0) && (lineStream.peek() == -1 || lineStream.peek() == 32)) {          //x_location cannot be negative
                                    lineStream >> y_location;

                                    if (!lineStream.fail() && (y_location >= 0) && (lineStream.peek() == -1 || lineStream.peek() == 32)) {      //y_location cannot be negative
                                        lineStream >> x_size;

                                        if (!lineStream.fail() && (x_size >= 0) && (lineStream.peek() == -1 || lineStream.peek() == 32)) {      //x_size cannot be negative
                                            lineStream >> y_size;

                                            if (!lineStream.fail() && (y_size >= 0) && (lineStream.peek() == -1 || lineStream.peek() == 32)) {  //y_size cannot be negative
                                                lineStream >> n;

                                                if (lineStream.eof() && lineStream.fail()) {
                                                    bool check_circleDim = true;                    //bool variable to check if the dimensions of the circle are valid (note: x_size and y_size have to be the same for a circle)

                                                    if (type == shapeTypesList[0] && y_size != x_size) {    //if x_size does not equal y_size
                                                        check_circleDim = false;                            //circle dimensions are invalid
                                                    }

                                                    if (check_circleDim) {                                  //if the dimensions of the circle are correct, proceed to create a new shape of type circle
                                                        if (shapeCount != max_shapes) {
                                                            Shape* newShape;

                                                            newShape = new Shape(name, type, x_location, x_size, y_location, y_size);

                                                            shapesArray[shapeCount] = newShape;
                                                            
                                                            shapeCount++;

                                                            cout << "Created ";
                                                            (newShape -> draw());
                                                        }
                                                        else {      //if shapeCount = max_shapes, the array is full!
                                                            sArray_full();
                                                        }
                                                    }
                                                    else {
                                                        invalid_val();      //if dimensions of the circle are invalid, then output invalid value error message
                                                    }
                                                }                    
                                                else {
                                                    excess_arg();       //if end of file is not reached, enough arguments are NOT present
                                                }
                                            }

                                            //if y_size is incorrect
                                            else {
                                                if (lineStream.fail()) {
                                                    if(lineStream.eof()) {
                                                        too_few_arg();
                                                    }
                                                    else {
                                                        invalid_arg();
                                                    }
                                                }
                                                else if (y_size < 0) {      //y_size cannot be negative
                                                    invalid_val();          //print invalid value error
                                                }
                                                else {
                                                    invalid_arg();
                                                }
                                            }
                                        }
                                        //if x_size is incorrect
                                        else {
                                            if (lineStream.fail()) {
                                                if (lineStream.eof()) {
                                                    too_few_arg();
                                                }
                                                else {
                                                    invalid_arg();
                                                }
                                            }
                                            else if (x_size < 0) {      //x_size cannot be negative
                                                invalid_val();          //print invalid value error
                                            }
                                            else {
                                                invalid_arg();
                                            }
                                        }
                                    }
                                    //if y_location is incorrect
                                    else {
                                        if (lineStream.fail()) {
                                            if (lineStream.eof()) {
                                                too_few_arg();
                                            }
                                            else {
                                                invalid_arg();
                                            }
                                        }
                                        else if (y_location < 0) {      //y_location cannot be negative
                                            invalid_val();              //print invalid value error
                                        }
                                        else {
                                            invalid_arg();
                                        }
                                    }
                                }
                                //if x_location fails
                                else {
                                    if (lineStream.fail()) {
                                        if (lineStream.eof()) {
                                            too_few_arg();
                                        }
                                        else {
                                            invalid_arg();
                                        }
                                    }
                                    else if (x_location < 0) {        //x_location cannot be negative
                                        invalid_val();                //print invalid value error
                                    }
                                    else {
                                        invalid_arg();
                                    }
                                }
                            }
                            //in the case: shape DNE
                            else {
                                invalid_shape_type();           //print invalid shape type error 
                            }
                        }
                        else{
                            if(lineStream.eof()) {
                                too_few_arg(); 
                            }
                        }
                    }
                }
                else {
                    if (lineStream.eof()) {
                        too_few_arg();   
                    }
                }
            }   
            
            else if (command == "move") {
                int x_location, y_location, x_size, y_size;
                string n, extra;

                lineStream >> n;

                if (!lineStream.fail()) {
                    Shape* s_find = shape_search(n);

                    if (s_find != NULL) {
                        lineStream >> x_location;
                        
                        if (!lineStream.fail() && (x_location >= 0) && (lineStream.peek() == -1 || lineStream.peek() == 32)) {
                            lineStream >> y_location;

                            //if valid argument
                            if (!lineStream.fail() && (y_location >= 0) && (lineStream.peek() == -1 || lineStream.peek() == 32)) {
                                lineStream >> extra;

                                if (lineStream.eof() && lineStream.fail()) {
                                    s_find->setXlocation(x_location);       //move to new x_location
                                    s_find->setYlocation(y_location);       //move to new y_location
                                    
                                    cout << "Moved " << s_find->getName() << " to " << s_find->getXlocation() << " " << s_find->getYlocation() << endl;
                                }            
                                else {
                                    excess_arg();
                                }
                            }
                            //if y_location fails
                            else {
                                if (lineStream.fail()) {
                                    if (lineStream.eof()) {
                                        too_few_arg();
                                    }
                                    else {
                                        invalid_arg();
                                    }
                                }
                                else if (y_location < 0) {
                                    invalid_val();
                                }
                                else {
                                    invalid_arg();
                                }
                            }
                        }
                        //if x_location fails
                        else {
                            if (lineStream.fail()) {
                                if (lineStream.eof()) {
                                    too_few_arg();
                                }
                                else {
                                    invalid_arg();
                                }
                            }
                            else if (x_location < 0) {
                                invalid_val();
                            }
                            else {
                                invalid_arg();
                            }
                        }

                    }
                    else {
                        shape_name_not_found(n); 
                    }
                }
                else {
                    if (lineStream.eof()) {
                        too_few_arg();   
                    }
                }
            }   
            
            //rotate
            else if (command == "rotate") {
                int rotate;
                string n, extra;

                lineStream >> n;

                if (!lineStream.fail()) {
                    Shape* s_find = shape_search(n);

                    if (s_find != NULL) {
                        lineStream >> rotate;

                        if (!lineStream.fail() && (rotate >= 0) && (rotate <= 360) && (lineStream.peek() == -1 || lineStream.peek() == 32)) {       //angle needs to be: 0<= angle <= 360
                            lineStream >> extra;

                            if (lineStream.eof() && lineStream.fail()) {
                                s_find->setRotate(rotate);
                                
                                cout << "Rotated " << s_find->getName() << " by " << rotate << " degrees" << endl;
                            }            
                            else {
                                excess_arg();
                            }
                        }
                        else {
                            if (lineStream.fail()) {
                                if (lineStream.eof()) {
                                    too_few_arg();
                                }
                                else {
                                    invalid_arg();
                                }
                            }
                            else if (rotate < 0 || rotate > 360) {      //angle cannot be negative or > 360
                                invalid_val();
                            }
                            else {
                                invalid_arg();
                            }
                        }

                    }
                    else {
                        shape_name_not_found(n);
                    }
                }
                else {
                    if (lineStream.eof()) {
                        too_few_arg();  
                    }
                }
            }   

            else if (command == "draw") {
                string n;
                
                lineStream >> n;

                if (!lineStream.fail()) {
                    string extra;

                    lineStream >> extra;
                    Shape* s_find = shape_search(n);

                    //if shape found
                    if (s_find != NULL) {
                        //if right amount of args
                        if (lineStream.eof() && lineStream.fail()) {
                            cout << "Drew ";
                            s_find->draw();
                            cout << endl;
                        }
                        else {
                           excess_arg();
                        }
                    }
                    else {
                        if (n == keyWordsList[0]) {         //for "draw all" shapes
                            if (lineStream.eof() && lineStream.fail()) {
                                cout << "Drew all shapes" << endl;
                                for (int i = 0; i < shapeCount; i++) {
                                    if (shapesArray[i] != NULL) {
                                        shapesArray[i] -> draw();
                                        //cout << endl; 
                                    }
                                }
                            }
                            else {
                                excess_arg();
                            }
                        }
                        else {
                            shape_name_not_found(n);
                        }
                    }
                }
                else {
                    too_few_arg();  
                }
            }   

            else if (command == "delete") {
                string n;
                
                lineStream >> n;

                if (!lineStream.fail()) {
                    string extra;

                    lineStream >> extra;
                    Shape* s_find = shape_search(n);

                    if (s_find != NULL) {
                        if (lineStream.eof() && lineStream.fail()) {
                            for (int i = 0; i < shapeCount; i++) {
                                if ((shapesArray[i] != NULL) && (n == shapesArray[i]-> getName())) {
                                    cout << "Deleted shape " << n << endl;          //to delete only ONE shape
                                    delete shapesArray[i];
                                    shapesArray[i] = NULL;                          //always set to NULL after deleting
                                    break;
                                }
                            }
                        }
                        else {
                            excess_arg();
                        }
                    }

                    else {
                        if (n == keyWordsList[0]) {         //for "delete all"
                            if (lineStream.eof() && lineStream.fail()) {
                                for (int i = 0; i < shapeCount; i++) {
                                    delete shapesArray[i];
                                    shapesArray[i] = NULL;      //always set to NULL after deleting
                                }
                                cout << "Deleted: all shapes" << endl;              //to delete ALL shapes
                            }
                            else {
                                excess_arg();
                            }
                        }
                        else {
                            shape_name_not_found(n);
                        }
                    }
                }
                else {
                    too_few_arg();
                }
            }  

            else {
                invalid_command();
            } 
        }

        lineStream.clear();             //check later if this statement is needed

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

/*
 takes an argument of type string
 * iterates through the array to find the shape passed in the argument
 */
Shape* shape_search(string name) {
    for (int i = 0; i < shapeCount; i++) {
        if (shapesArray[i] != NULL) {
            if (((shapesArray[i])->getName()) == name) {
                return shapesArray[i];
            }
        }
    }
    return NULL;
}

void invalid_command(){
    cout << "Error: invalid command" << endl;
}

void invalid_arg(){
    cout << "Error: invalid argument" << endl;
}

void invalid_shape_name(){
    cout << "Error: invalid shape name" << endl;
}

void shape_name_exists(string nameofShape){
    cout << "Error: shape " << nameofShape << " exists" << endl;
}

void shape_name_not_found(string nameofShape){
    cout << "Error: shape " << nameofShape << " not found" << endl;
}

void invalid_shape_type(){
    cout << "Error: invalid shape type" << endl;
}

void invalid_val(){
    cout << "Error: invalid value" << endl;
}

void excess_arg(){
    cout << "Error: too many arguments" << endl;
}

void too_few_arg(){
    cout << "Error: too few arguments" << endl;
}

void sArray_full(){
    cout << "Error: shape array is full" << endl;
}

/*
Function that deletes the ARRAY 
 */
void del_array() {

    for (int i = 0; i < shapeCount; i++) {
        delete shapesArray[i];
        shapesArray[i] = NULL;      //always set to NULL after deleting
    }

    delete [] shapesArray;          //cannot do delete shapesArray bc we want to delete of type array
    shapesArray = NULL;             //always set to NULL after deleting

    shapeCount = 0;                 //set shapeCount to 0 since we have deleted all shapes
}