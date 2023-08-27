#include "Board.h"

float minimax(String pos, int depth, bool player){
	
	int status = winLoseDraw(pos);									
	if (status!=2) { return (status*((player)?1.f:-1.f)/(depth+1)); }

	float  child_node_eval, 
	       evaluation = 3;
	char   player_char = (player)?'x':'o';  
	String variant;                         
	
	for(int i=0; i<=8; i++){ 
		if(pos[i]!=' '){ continue; }                                 
		variant = pos;                      
		variant[i] = player_char;           
		child_node_eval = -minimax(variant, (depth+1), !player);
		evaluation = (child_node_eval>evaluation || evaluation==3)?child_node_eval:evaluation;
	}
	return evaluation;
}

//=============================================================================================================


int bestMove(String pos, bool player)
{

	float  child_node_eval, 
			evaluation = 3;
	int    best_move;
	char   player_char = (player)?'x':'o';
	String variant;

	// Uncomment for measuring time. 
	// float etime, stime = millis()/1000.f;

	for(int i=0; i<=8; i++){ 
		if(pos[i]!=' '){ continue; }
		variant = pos;
		variant[i] = player_char;
		child_node_eval = -minimax(variant, 0, !player);
		if(child_node_eval>evaluation || evaluation==3){
			evaluation = child_node_eval;
			best_move = i;
		}
	}

	// Uncomment for measuring time & output the measurement.
	// float absolute_eval = evaluation*((player)?1:-1);
	// etime = (millis()/1000.f)-stime;
	// Serial.println("\n-------------------------------------------------");
	// Serial.print("[Evaluation: ");
	// Serial.print(absolute_eval);
	// Serial.print(" ]\n[Duration   : ");
	// Serial.print(etime);
	// Serial.println("s ]");
	// Serial.println("-------------------------------------------------\n");

	return best_move;
	
}
