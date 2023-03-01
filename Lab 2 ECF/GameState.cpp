//
//  GameState.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//

#include "globals.h"
#include "GameState.h"

// ECE244 Student: add you code below

//constructor
GameState::GameState(){
    selectedRow = 0;
    selectedColumn = 0;
    moveValid = true;
    gameOver = false;
    winCode = 0;
    turn = true;

    for (int i = 0; i < boardSize; i++){            //Sets the value for each slot in the gameBoard to 0 (0 ~ empty)
        for (int j = 0; j < (boardSize); j++){
            gameBoard[i][j] = Empty;
        }
    }
}

// Return the selected row (in the range 0..boardSize-1)
int GameState::get_selectedRow(){
    return selectedRow;
}  

// Return the selected column (in the range 0..boardSize-1)
int GameState::get_selectedColumn(){
    return selectedColumn;
}

// Set the selected row to value in the range (in the range 0..boardSize-1)
// An out of range value is ignored and the function just returns
void GameState::set_selectedRow(int value){

    if ((value >= 0) && (value <= (boardSize-1))){
        selectedRow = value;
    }
    else{
        return;
    }

}     

// Set the selected column in the range (in the range 0..boardSize-1)
// An out of range value is ignored and the function just returns
void GameState::set_selectedColumn(int value){

    if ((value >= 0) && (value <= (boardSize-1))){
        selectedColumn = value;
    }
    else{
        return;
    }
} 

// Get the moveValid value
bool GameState::get_moveValid(){
    return moveValid;
}

// Set the moveValid variable to value
void GameState::set_moveValid(bool value){
    moveValid = value;
}

// Get the gameOver value
bool GameState::get_gameOver(){
    return gameOver;
}

// Set the gameOver variable to value
void GameState::set_gameOver(bool value){
    gameOver = value;
}

// Get the winCode [0..8]
int GameState::get_winCode(){
    return winCode;
}

// Set the winCode to value in the range (0..8)
// An out of range value is ignored and the function just returns
void GameState::set_winCode(int value){

    if ((value >= 0) && (value <= 8)){
        winCode = value;
    }
    else{
        return;
    }
}

// Get the value of turn
bool GameState::get_turn(){
    return turn;
}

// Set the value of turn
void GameState::set_turn(bool value){
    turn = value;       //if value = true, turn = true; if value = false, turn = false
}

// Get the game board value at the board location at row and col
// This method checks that row, col and value are in range/valid
// and if not it returns Empty
int GameState::get_gameBoard(int row, int col){

    if ((row <= (boardSize-1)) && (row >= 0) && (col <= (boardSize-1)) && (col >= 0)){
        return gameBoard[row][col];
    }
    else{
        gameBoard[row][col] = Empty;
        return gameBoard[row][col];
    }

}

// Set the game board value at the board location at row and col to value
// This method checks that row, col and value are in range/valid and if not it
// just returns
void GameState::set_gameBoard(int row, int col, int value){
    //will need nested if statements (outer one to check for board requirements, inner one to check for move requirements)

    if ((row <= (boardSize-1)) && (row >= 0) && (col <= (boardSize-1)) && (col >= 0) && ((value == 1) || (value == -1))){ //if condition to check if 0 <= row < 2 (2 ~ < boardSize) and <= 0 < col
        //if ((value == 1) || (value == -1)){     //if conditions checks if the input values are valid: -1, 0, 1 (0 represents empty slot)
        gameBoard[row][col] = value;
        //}
    }
    else{
        return;
    }
}

