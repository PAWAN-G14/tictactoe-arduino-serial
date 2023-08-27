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

*/

#include <Arduino.h>
#include <Game.h>

void setup() {
	// Setting up the serial monitor @9600 baud rate
	Serial.begin(9600); 
}

void loop() {
  
	Game game;	// Initializing the game

	// Game Loop
	while(game.status==2){
		game.userTurn();
		game.computerTurn();
		game.updateStatus();
	}

}

