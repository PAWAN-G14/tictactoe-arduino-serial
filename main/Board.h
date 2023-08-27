int winLoseDraw(String pos){
 
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

    public:
        char pos[9] = {' ',' ',' ',          
                       ' ',' ',' ',
                       ' ',' ',' '};
        bool makeMove(int cell, bool role);   
        int  checkStatus();                   
        void draw();                          
};

bool Board::makeMove(int cell, bool role){
    if(cell<0 || cell>8 || pos[cell]!=' '){ return 1; }
    pos[cell] = (role)?'x':'o';
    return 0;
}


int Board::checkStatus(){ return winLoseDraw(pos); }

void Board::draw(){

  Serial.println("\t   |   |\n\t "+String(pos[0])+" | "+String(pos[1])+" | "+String(pos[2])+"\n\t   |   |");
  Serial.println("\t-----------");
  Serial.println("\t   |   |\n\t "+String(pos[3])+" | "+String(pos[4])+" | "+String(pos[5])+"\n\t   |   |");
  Serial.println("\t-----------");
  Serial.println("\t   |   |\n\t "+String(pos[6])+" | "+String(pos[7])+" | "+String(pos[8])+"\n\t   |   |\n");
  
}
