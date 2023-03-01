//
//  playMove.cpp
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
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"

//
void playMove(GameState& game_state) {
    
    bool tie = false;
    int temp;
    int code_counter = 0;
    int winCode_arr[7];
    for (int i = 0; i < 8; i++) {
        winCode_arr[i] = 0;
    }
    
    // Check if move is valid corresponding to the user's input
    if((game_state.get_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn()) == X) || (game_state.get_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn()) == O))
    {
        game_state.set_moveValid(false);
    }
    else
    {
        game_state.set_moveValid(true);
    }

    // Set the game board as required by the inputs from the user
    if(game_state.get_moveValid() == true)
    {
        if(game_state.get_turn() == true)
        {
            game_state.set_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn(), 1); // Place X (+1)
        }
        
        else
        {
            game_state.set_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn(), -1); // Place O (-1)
        }
    }

    //algorithm to check winCodes
    if(((game_state.get_gameBoard(2,0)==X) && (game_state.get_gameBoard(1,1)==X) && (game_state.get_gameBoard(0,2)== X)) || ((game_state.get_gameBoard(2,0)== O) && (game_state.get_gameBoard(1,1)==O) && (game_state.get_gameBoard(0,2)==O)))
    {
        game_state.set_winCode(8);
//        code_counter++;
//        winCode_arr[7] = 8;
    }
    else if(((game_state.get_gameBoard(0, 0)==X) && (game_state.get_gameBoard(1, 1)==X) && (game_state.get_gameBoard(2, 2)== X)) || ((game_state.get_gameBoard(0, 0)== O) && (game_state.get_gameBoard(1, 1)== O) && (game_state.get_gameBoard(2, 2)== O)))
    {
        game_state.set_winCode(7);
//        code_counter++;
//        winCode_arr[6] = 7;
    }
    else if(((game_state.get_gameBoard(0, 2)==X) && (game_state.get_gameBoard(1, 2)==X) && (game_state.get_gameBoard(2, 2)== X)) || ((game_state.get_gameBoard(0, 2)==O) && (game_state.get_gameBoard(1, 2)==O) && (game_state.get_gameBoard(2, 2)==O)))
    {
        game_state.set_winCode(6);
//        code_counter++;
//        winCode_arr[5] = 6;
    }
    else if(((game_state.get_gameBoard(0,1)==X) && (game_state.get_gameBoard(1, 1)==X) && (game_state.get_gameBoard(2, 1)== X)) || ((game_state.get_gameBoard(0, 1)==O) && (game_state.get_gameBoard(1, 1)==O) && (game_state.get_gameBoard(2, 1)==O)))
    {
        game_state.set_winCode(5);
//        code_counter++;
//        winCode_arr[4] = 5;
    }
    else if(((game_state.get_gameBoard(0,0)==X) && (game_state.get_gameBoard(1,0)==X) && (game_state.get_gameBoard(2, 0)== X)) || ((game_state.get_gameBoard(0, 0)==O) && (game_state.get_gameBoard(1, 0)==O) && (game_state.get_gameBoard(2, 0)==O)))
    {
        game_state.set_winCode(4);
//        code_counter++;
//        winCode_arr[3] = 4;
    }
    else if(((game_state.get_gameBoard(2,0)==X) && (game_state.get_gameBoard(2,1)==X) && (game_state.get_gameBoard(2, 2)== X)) || ((game_state.get_gameBoard(2, 0)==O) && (game_state.get_gameBoard(2, 1)==O) && (game_state.get_gameBoard(2, 2)==O)))
    {
        game_state.set_winCode(3);
//        code_counter++;
//        winCode_arr[2] = 3;
    }
    else if(((game_state.get_gameBoard(1,0)==X) && (game_state.get_gameBoard(1,1)==X) && (game_state.get_gameBoard(1, 2)== X)) || ((game_state.get_gameBoard(1, 0)==O) && (game_state.get_gameBoard(1, 1)==O) && (game_state.get_gameBoard(1, 2)==O)))
    {
        game_state.set_winCode(2);
//        code_counter++;
//        winCode_arr[1] = 2;
    }
    else if(((game_state.get_gameBoard(0,0)==X) && (game_state.get_gameBoard(0,1)==X) && (game_state.get_gameBoard(0, 2)==X)) || ((game_state.get_gameBoard(0, 0)==O) && (game_state.get_gameBoard(0, 1)==O) && (game_state.get_gameBoard(0, 2)==O)))
    {
        game_state.set_winCode(1);
//        code_counter++;
//        winCode_arr[0] = 1;
    }
    else
    {
        game_state.set_winCode(0);
    }
    
    if((game_state.get_winCode() == 1) || (game_state.get_winCode() == 2) || (game_state.get_winCode() == 3) || (game_state.get_winCode() == 4) || (game_state.get_winCode() == 5) || (game_state.get_winCode() == 6) || (game_state.get_winCode() == 7) || (game_state.get_winCode() == 8))
    {
        game_state.set_gameOver(true);
    }
    else
    {
        game_state.set_gameOver(false);
    }
    
//    if (code_counter > 1) {
//        for (int i = 0; i < 8; i++) {
//            for (int j = i + 1; j < 8; j++) {
//                if (winCode_arr[i] < winCode_arr[j]) {
//                    temp = winCode_arr[i];
//                    winCode_arr[i] = winCode_arr[j];
//                    winCode_arr[j] = temp;
//                }
//            }
//        }
//
//        game_state.set_winCode(winCode_arr[0]);
//        game_state.set_gameOver(true);
//
//    }
    
    if(game_state.get_winCode() == 8){
        game_state.set_winCode(8);
    }
    else if(game_state.get_winCode() == 7){
        game_state.set_winCode(7);
    }
    else if(game_state.get_winCode() == 6){
        game_state.set_winCode(6);
    }
    else if(game_state.get_winCode() == 5){
        game_state.set_winCode(5);
    }
    else if(game_state.get_winCode() == 4){
        game_state.set_winCode(4);
    }
    else if(game_state.get_winCode() == 3){
        game_state.set_winCode(3);
    }
    else if(game_state.get_winCode() == 2){
        game_state.set_winCode(2);
    }
    else if(game_state.get_winCode() == 1){
        game_state.set_winCode(1);
    }
    
    int counter = 0;
    //check for a tie
    for (int i = 0; i <= (boardSize-1); i++){
        for (int j = 0; j <= (boardSize-1); j++){
            if (game_state.get_gameBoard(i,j) != Empty){
                counter++;
            }
        }
    }
    
    //if counter is 9, i.e, all the positions of the 3x3 matrix are full
    if (counter == 9){
        game_state.set_gameOver(true);
    }
    
    //algorithm to change turn
    if((game_state.get_gameOver() == false) && (game_state.get_moveValid() == true))    //if game is not over and the move is valid, change turn
    {
        if(game_state.get_turn() == true)
        {
            game_state.set_turn(false);
        }
        else
        {
            game_state.set_turn(true);
        }
    }
    
}