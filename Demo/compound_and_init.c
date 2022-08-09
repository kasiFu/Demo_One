/*
 *  This module is no longer used.  It has been replaced by "dishwasher_fsm.c".
 */
 
#if 0

enum statusValues {
    allGood,
    notInitialized,
	stateOneProblem,
	stateTwoProblem,
	stateThreeProblem,
	stateFourProblem
	};

enum stateValues { 
    S_INIT = 0,
    S_ONE = 1,
    S_TWO = 2,
	S_THREE = 3 ,
	S_FOUR = 4,
} ;
static enum stateValues currentState = 999;


static enum statusValues doStateOneStuff () {
   /* Not Implemented */
   return stateOneProblem;
}

static enum statusValues doStateTwoStuff () {
   /* Not Implemented */
   return stateTwoProblem;
}

static enum statusValues doStateThreeStuff () {
   /* Not Implemented */
   return stateThreeProblem;
}

static enum statusValues doStateFourStuff () {
   /* Not Implemented */
   return stateFourProblem;
}

int initalizeStateMachine () {
   currentState = S_INIT;
   }


enum statusValues stateTranstion (enum stateValues newState) {

   int localStatus;

   /* Ensure that the state machine has been initialized */
   if (currentState == S_INIT) {
	   switch (newState) {
		 case S_ONE :
			localStatus = doStateOneStuff ();
			break;
		 case S_TWO :
			localStatus = doStateTwoStuff ();
			break;
		 case S_THREE :
			localStatus = doStateThreeStuff ();
			break;
		 case S_FOUR :
			localStatus = doStateFourStuff ();
			break;
		}
		currentState=newState;
		return localStatus;
	}
	else
	   return notInitialized;
	}


#endif



