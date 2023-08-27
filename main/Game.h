#include "AI.h"

class Game{
    private:
        Board board;
        bool user_role;
    public:
        int status=2;
        void updateStatus();
        void computerTurn();
        void userTurn();
        Game();
};


Game::Game(){

    while(1){
        Serial.println("What would you prefer, X or O ? . . .");
        while(Serial.available() == 0){}
        String user_input = Serial.readString();
        user_input.trim();
        if     (user_input[0]=='x' || user_input[0]=='X'){ user_role=1; }
        else if(user_input[0]=='o' || user_input[0]=='O'){ user_role=0; }
        else {
            Serial.println("Sorry, seems to be an invalid input . . . Try Again. ");
            continue;
        }
        break;
    }

    if(user_role){
        updateStatus();
        userTurn();
        if (board.makeMove(4, !user_role)){ board.makeMove(0, !user_role); }
    }
    else{ board.makeMove(4, !user_role); }
    updateStatus();

}


void Game::updateStatus(){
   
    Serial.println("======================================================\n");
    board.draw();
    Serial.println("");
    status = board.checkStatus();
    if (status==2){
        Serial.println("Your Move.\n");
    }
    else if(status==0){
        Serial.println("IT'S A TIE!\n");
    }
    else{
        Serial.println("Computer Wins. Better Luck next time . . .\n");
    }
}


void Game::userTurn(){
    
    while(1){

        while(Serial.available() == 0){}
        String user_input = Serial.readString();
        user_input.trim();
        if (!isDigit(user_input[0]) || board.makeMove(String(user_input[0]).toInt()-1, user_role))
        {
            Serial.println("Sorry, seems to be an invalid input . . . Try Again. ");
            Serial.println("Your Move.\n");
            continue;
        }
        break;
    }
}

void Game::computerTurn(){ board.makeMove(bestMove(board.pos, !user_role), !user_role); }
