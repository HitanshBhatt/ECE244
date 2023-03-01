//
//  main.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iostream>
#include <string>
using namespace std;

#include "globals.h"
#include "GameState.h"

// Function prototype for playMove
void playMove(GameState &);

// The main function
int main()
{

    /**********************************************************************************/
    /* Create an initialized game state object                                        */
    /**********************************************************************************/
    GameState game_state;

    // Read two integers from the user that represent the row and column
    // the player would like to place an X or an O in
    // You can assume there will be no formatting errors in the input

    int row;
    int col;
    char move;
    string validMove, gameOver;
    while (!game_state.get_gameOver())
    {
        cout << "Enter row and column of a grid cell: ";
        cin >> row >> col;

        // Check that the read row and column values are valid grid coordinates
        if ((row < 0) || (row > 2) || (col < 0) || (col > 2))
        {
            cout << "Invalid board coordinates " << row << " " << col << endl
                 << endl;
            continue;
        }
        // The coordinates are valid; set the selectedRow and selectedColumn
        // members of the game state to the read values
        // Again, the corresponding mutators of GameState must be first
        // implemented before this works
        // ECE244 Student: add your code here
        game_state.set_selectedRow(row);
        game_state.set_selectedColumn(col);

        // Call playMove

        playMove(game_state);

        // ECE244 Student: add your code here

        // Print the GameState object, as prescribed in the handout

        // ECE244 Student: add your code here
        cout << "Selected row " << row << " and column " << col << endl;
        cout << "Game state after playMove: \n";
        cout << "Board: \n";


        /*
            Board formatting:
               B B B
               B B B
               B B B

               00 01 02
               10 11 12
               20 21 22
        */
        for (int i = 0; i < boardSize; i++)
        {
            cout << "   ";      //3 spaces before each board value as required by the lab handout
            for (int j = 0; j < boardSize; j++)
            {
                switch(game_state.get_gameBoard(i,j)){
                    case (-1):
                        move = 'O';
                        break;
                    case(0):
                        move = 'B';
                        break;
                    case(1):
                        move = 'X';
                        break;
                    default:
                        move = 'B';
                        break;
                }
                // if (game_state.get_gameBoard(i, j) == O)
                //     move = 'O';
                // else if (game_state.get_gameBoard(i, j) == X)
                //     move = 'X';
                // else if (game_state.get_gameBoard(i, j) == Empty)
                //     move = 'B';

                cout << move << " ";       //output move with a space as required by the lab document
            }
            cout << endl;
        }

        if (game_state.get_moveValid() == true){
            validMove = "true";                     //print "true" if the move is valid
        }
        else{
            validMove = "false";                    //print "false" if the move is not valid
        }

        if (game_state.get_gameOver() == true){
            gameOver = "true";                      //print "true" if the game is over
        }
        else{
            gameOver = "false";                     //print "false" if the game is not over
        }


        cout << "moveValid: " << validMove << endl;
        cout << "gameOver: " << gameOver << endl;
        cout << "winCode: " << game_state.get_winCode() << endl;
    }

    // add "return 0;"  ; keeps giving 'main function returned a non-zero value'
    return 0;
}
