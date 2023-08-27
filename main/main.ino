/*
--------------------------------------------
Simple TicTacToe AI using Minimax algorithm.
--------------------------------------------

............................................
Runs on an Arduino (UNO in this case),using
Serial monitor as the interface.
............................................

 - - - - - - - - - - - - - - - - - - - - 
 Author: Pawan G.
 Status: 14 y/o still learning.
 - - - - - - - - - - - - - - - - - - - - 

NOTE: This code is undocumeted to keep up the minimalism of this branch.
      For documented code, please, go refer the main repo at https://github.com/PAWAN-G14/tictactoe-arduino-serial.
      In the main branch, checkout /src for main.ino and /include for AI.h, Game.h and Board.h

*/

#include "Game.h"

void setup() { Serial.begin(9600); }

void loop() {
	Game game;
	while(game.status==2){
		game.userTurn();
		game.computerTurn();
		game.updateStatus();
	}
}
