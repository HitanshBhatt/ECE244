//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

#include "Shape.h"
#include "Triangle.h"

Triangle::Triangle (string n, float xcent, float ycent, float x_coord1, float y_coord1, float x_coord2, float y_coord2, float x_coord3, float y_coord3){
    x1 = x_coord1;
    y1 = y_coord1;

    x2 = x_coord2;
    y2 = y_coord2;

    x3 = x_coord3;
    y3 = y_coord3;
}

Triangle::~Triangle(){

}

/* Accessors: */
float Triangle::get_x1() const{
    return x1;
}

float Triangle::get_y1() const{
    return y1;
}

float Triangle::get_x2() const{
    return x2;
}

float Triangle::get_y2() const{
    return y2;
}

float Triangle::get_x3() const{
    return x3;
}

float Triangle::get_y3() const{
    return y3;
}

/* Mutators: */
void Triangle::set_x1(float x_1){
    x1 = x_1;
}

void Triangle::set_y1(float y_1){
    y1 = y_1;
}

void Triangle::set_x2(float x_2){
    x2 = x_2;
}

void Triangle::set_y2(float y_2){
    y2 = y_2;
}

void Triangle::set_x3(float x_3){
    x3 = x_3;
}

void Triangle::set_y3(float y_3){
    y3 = y_3;
}
        
/* Helper Functions */
void Triangle::draw() const{
    cout << std::fixed;
    cout << std::setprecision(2);

    cout << "triangle: " << name << " " << x_centre << " " << y_centre << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << computeArea() << endl;
}

float Triangle::computeArea() const{
    float a;
    a = ((0.5)*abs((x1*(y2 - y3)) - (x2*(y1 - y3)) + (x3*(y1 - y2))));
    return a;
}

Shape* Triangle::clone() const{
    return (new Triangle(*this));
}