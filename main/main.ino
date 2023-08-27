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
