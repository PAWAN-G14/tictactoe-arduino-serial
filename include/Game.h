#include <Arduino.h>
#include <AI.h>

class Game{

    /****************************************************************************************************
     
     The Game class contains the following functionalities: 

     * Setting up the board with the initial position.
     * Begins the game.
     * Drawing the board on the serial monitor
     * Prompts the user to make the move and makes the move according to the reply.
     * Making moves on the board on behalf of the computer/AI.
     * Checking the status of the game with each iteration and displaying the results.
     
    ****************************************************************************************************/

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

    /****************************************************************************************************
     * The constructor of the Game class.
     * Asks the user to select a role i.e 'x' or 'o'.
     * Manages invalid inputs.
     * Asks the user to make the first move.
     * Makes the first move of the computer.
        -> NOTE: the First move is theory, i.e its not actually calculated and evaluated by minimax().
            This is because it will take a lot of time to lookup all the possible moves and responses,
            that too in an 8-bit mcu like atmega328 that has a max operating frequency of 20Mhz.
        -> If the computer is 'x' and goes first, then 'x' is placed in the centre square,
           i.e, square of index 4.
        -> If the user goes first, then that move is made by getting the user's input.
            Then, by theory, if the centre square (square 4) is free, then 'o' is placed in it.
            If the centre square is not free, then 'o' is placed in the top left corner, i.e 
            in square 0.
    ****************************************************************************************************/

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
    
    /****************************************************************************************************
     * @return void
     * Draws the board and displays the current status of the game.
     * Checks whether the game ended and displays the results.
    ****************************************************************************************************/

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
    
    /****************************************************************************************************
     * @return void
     * Prompts the user to input the square number in which 'x' or 'o' has to be placed.
     * Makes the move w.r.t to user's input.
     * Manages invalid inputs.
    ****************************************************************************************************/

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


void Game::computerTurn(){ 

    /****************************************************************************************************
     * @return void
     * Gets the best move from the position's analysis and evaluation obtained by minimax algorithm
     * Makes the best move move.
    ****************************************************************************************************/
    board.makeMove(bestMove(board.pos, !user_role), !user_role); 

}
