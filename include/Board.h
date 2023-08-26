#include<Arduino.h>

int winLoseDraw(String pos){

    /****************************************************************************************************
     * @return status type<bool>
     * @param pos i.e the position to be checked. Type<int>
     * Checks whether the game ended and gets the results, which are as follows . . .
        - If return  1: x wins
        - If return -1: o wins
        - If return  0: tie
        - If return  2: Game did not end
    ****************************************************************************************************/

    if(
        (pos[0]=='x' && pos[3]=='x' && pos[6]=='x') || 
        (pos[1]=='x' && pos[4]=='x' && pos[7]=='x') || 
        (pos[2]=='x' && pos[5]=='x' && pos[8]=='x') || 
        (pos[0]=='x' && pos[4]=='x' && pos[8]=='x') || 
        (pos[2]=='x' && pos[4]=='x' && pos[6]=='x') || 
        (pos[0]=='x' && pos[1]=='x' && pos[2]=='x') || 
        (pos[3]=='x' && pos[4]=='x' && pos[5]=='x') || 
        (pos[6]=='x' && pos[7]=='x' && pos[8]=='x')
      )                          { return 1; }
    else if(
        (pos[0]=='o' && pos[3]=='o' && pos[6]=='o') || 
        (pos[1]=='o' && pos[4]=='o' && pos[7]=='o') || 
        (pos[2]=='o' && pos[5]=='o' && pos[8]=='o') || 
        (pos[0]=='o' && pos[4]=='o' && pos[8]=='o') || 
        (pos[2]=='o' && pos[4]=='o' && pos[6]=='o') || 
        (pos[0]=='o' && pos[1]=='o' && pos[2]=='o') || 
        (pos[3]=='o' && pos[4]=='o' && pos[5]=='o') || 
        (pos[6]=='o' && pos[7]=='o' && pos[8]=='o')
      )                          { return -1; }
    else                         { for(char s : pos){ if(s==' '){ return 2; } }  return 0; }
}

//=========================================================================================================

class Board{

    /****************************************************************************************************
     
     The Board class contains the following properties and functionalities: 

     * Setting up the initial position
     * Checking the status of the game
     * Making moves
     * Drawing the board on the serial monitor
     
    ****************************************************************************************************/

    public:
        char pos[9] = {' ',' ',' ',           // Initial position
                       ' ',' ',' ',
                       ' ',' ',' '};
        bool makeMove(int cell, bool role);   // Places 'x' or 'o' in a given square.
        int  checkStatus();                   // Checks whether the game ended and gets the results.
        void draw();                          // Draws the board on the Serial monitor.
};

bool Board::makeMove(int cell, bool role){

    /****************************************************************************************************
     * @return success type<bool> (false for successful operation and vice-versa).
     * @param cell type<int> i.e the square's number in which 'x' or 'o' should be placed.
     * @param role type<bool> i.e to place 'x' (if true) and 'o' (if false).
     * Checks whether the square is empty and places 'x' or 'o' w.r.t role
    ****************************************************************************************************/

    if(cell<0 || cell>8 || pos[cell]!=' '){ return 1; }
    pos[cell] = (role)?'x':'o';
    return 0;
}

// Checks whether the game Ended and gets the results 
int Board::checkStatus(){ return winLoseDraw(pos); }

void Board::draw(){

  /****************************************************************************************************
   * @return void
   * The function that draws the board on the serial monitor
  ****************************************************************************************************/

  Serial.println("\t   |   |\n\t "+String(pos[0])+" | "+String(pos[1])+" | "+String(pos[2])+"\n\t   |   |");
  Serial.println("\t-----------");
  Serial.println("\t   |   |\n\t "+String(pos[3])+" | "+String(pos[4])+" | "+String(pos[5])+"\n\t   |   |");
  Serial.println("\t-----------");
  Serial.println("\t   |   |\n\t "+String(pos[6])+" | "+String(pos[7])+" | "+String(pos[8])+"\n\t   |   |\n");
  
}
