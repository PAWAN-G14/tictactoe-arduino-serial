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

