#include <Arduino.h>
#include <Board.h>

float minimax(String pos, int depth, bool player){

	/****************************************************************************************************
	 * @return evaluation of the position W.R.T to the player. type<float>
	 * @param  pos    type<String> the position to be evaluated.
	 * @param  depth  type<int>    the depth of the current node.
	 * @param  player type<bool>   true for 'x' and false for 'o'.
	 * This function is the implementation of minimax algorithm for evaluating the best moves,
	    the best responses and finally obtaining the evaluation, w.r.t the player.
	****************************************************************************************************/

	// Checking whether the it is the end position and the final result(status) is returned.
	// winLoseDraw() returns 0 for draw, 1 for x's victory, -1 for o's victory and 2 if the game did not end.

	int status = winLoseDraw(pos);									
	if (status!=2) { return (status*((player)?1.f:-1.f)/(depth+1)); }

	// If the game ended, then, before returning
	// -> status is multipled by -1 if player is 'o', because from o's point of view, -1 is a win
	//    (should denoted by +1) and 1 is a loss(should be denoted by -1). Or else, if player is 'x',
	//    no changes have to be done, so status is multiplied by 1.
	// -> Then, the status is divided by depth+1 (+1 to avoid zero division error) because the magnitude of the
	//    win/defeat should be reduced with increasing evaluation depths. The reason for this is that
	//    closer wins/losses should be given more weight than delayed wins/losses.
	// -> NOTE: The 1 or -1 by which status is multiplied are floats, not integers. This is because, the final
	//          evaluation (return value) should be a floating point value for it to be accurate. So by doing this, 
	//          the status value will be implicitly converted to float.

	// Some neccessary vairables.
	float  child_node_eval, 				// evaluation of a particular variation.
			evaluation = 3;					// best evaluation so far.
	char   player_char = (player)?'x':'o';  // converts the boolean notation of the player's role to 'x' or 'o'.
	String variant;                         // A particular variation of the position.
	// NOTE: Here, evaluation can only be a value between 1.0 and -1.0 . It is initialized with 3 as an exception.
	//		 This exception is used to denote that no evaluation has been set yet. 
	//       There should be an actual evaluation of an actual variant to begin with.

	// The for loop in which the variants are created (by going through each square) and evaluated.
	for(int i=0; i<=8; i++){ 

		if(pos[i]!=' '){ continue; }        // if the current square is not empty, 
		                                    // then, skip to the next loop as no variant can be created.

		// Making a possible move and creating a variant by placing 'x' or 'o' in the empty square.
		variant = pos;                      
		variant[i] = player_char;           

		// Recursively calling minimax() to get the evaluation of the current variant from the child node.
		// Here the evaluation is made negative because minimax() will return the evaluation from 
		// the opponent's POV. A bad evaluation for opponent is a good evaluation for us and vice-versa.
		child_node_eval = -minimax(variant, (depth+1), !player);
		evaluation = (child_node_eval>evaluation || evaluation==3)?child_node_eval:evaluation;
		// If evaluation is not set (i.e if valuation==3), or the evaluation of the current move/variation is more
		// than the best evaluation so far, then this current child node's evaluation is set as the best one.
		
	}

	// Returning the evaluation
	return evaluation;

}

//=============================================================================================================


int bestMove(String pos, bool player)
{

	/****************************************************************************************************
	 * @return number of the best square in which 'x' or 'o' has to be placed. type<int>
	 * @param  pos    type<String> the position to be evaluated.
	 * @param  player type<bool>   true for 'x' and false for 'o'.
	 * Gets the evaluations of the the possible variations by making the possible moves, compares them
	    and finds the best move, i.e the best square.
	****************************************************************************************************/

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

	// Uncomment for measuring time output the measurement.
	// float absolute_eval = evaluation*((player)?1:-1);
	// etime = (millis()/1000.0)-stime;
	// Serial.println("\n-------------------------------------------------");
	// Serial.print("[Evaluation: ");
	// Serial.print(absolute_eval);
	// Serial.print(" ]\n[Duration   : ");
	// Serial.print(etime);
	// Serial.println("s ]");
	// Serial.println("-------------------------------------------------\n");

	return best_move;
	
}