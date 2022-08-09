
/*
 *  This module simulates the control of a simple dishwasher appliacance, by using
 *  a Finite State Machine (FSM).  The states are pretty simple, going from IDLE through
 *  the normal WASH-RINSE-DRY cycles.  These states are defined in the enumerator
 *  "t_machine_state".  The events that can occur are defined below by "t_event".
 *
 */

enum eventValues { 
    EVENT_START_WASH,
    EVENT_START_RINSE,
    EVENT_START_DRY,
    EVENT_STOP,
};
typedef enum eventValues t_event;

enum stateValues { 
    STATE_IDLE,
    STATE_WASHING,
    STATE_RINSING,
    STATE_DRYING,
} ;
typedef enum stateValues t_machine_state;

//
//  Error Status Codes
//
enum e_status {
    STS_ALL_GOOD,
    STS_NO_POWER,
    STS_UNEXPECTED_EVENT,
    STS_NO_HEAT,
    STS_GENERAL_ERROR
    };
typedef enum e_status t_status;

// Module Level Global Data:
static t_machine_state currentState = STATE_IDLE;
static int powerOn = 0;

//
//  Not implemented yet.  Return All Good for now.
//
static t_status checkHeatingElement( void )
{
    return( STS_ALL_GOOD );
}

/*
 *  Process events while in the IDLE State/Cycle
 */
static t_status processIdleState (t_event event) {

    t_status sts;
 
    switch (event)
    {
        case EVENT_START_WASH:
            if (powerOn)
            {
                sts = STS_ALL_GOOD;
                currentState = STATE_WASHING;  // Go to Wash Cycle
            }
            else
                sts = STS_NO_POWER;
            break;

        case EVENT_STOP:
            sts = STS_ALL_GOOD;   // Stopping while Idle is okay.  Just stay in Idle state.
            break;

        default:                 //  Anything else that comes in is invalid.
            sts = STS_UNEXPECTED_EVENT;
            break;
    }

   return sts;
}

/*
 *  Process events while during the WASH Cycle.
 */
static t_status processWashCycle (t_event event)
{
    t_status sts;
 
    switch (event)
    {
        case EVENT_START_RINSE:
            if (powerOn)
            {
                sts = STS_ALL_GOOD;  
                currentState = STATE_RINSING;  // Go to Rinse Cycle
            }
            else
                sts = STS_NO_POWER;
            break;

        case EVENT_STOP:
            sts = STS_ALL_GOOD;  
            currentState = STATE_IDLE;  // Go back to the Idle State
            break;

        default:                 //  Anything else that comes in is invalid.
            sts = STS_UNEXPECTED_EVENT;
            break;
    }

   return sts;
}

static t_status processRinseCycle (t_event event)
{
    t_status sts;
 
    switch (event)
    {
        case EVENT_START_DRY:
            if (powerOn)
            {
                sts = checkHeatingElement();
                if (sts == STS_ALL_GOOD)
                    currentState = STATE_DRYING;
                else
                    currentState = STATE_IDLE;  // Go back to the Idle State
            }
            else
                sts = STS_NO_POWER;
            break;

        case EVENT_STOP:
            sts = STS_ALL_GOOD;  
            currentState = STATE_IDLE;  // Go back to the Idle State
            break;

        default:                 //  Anything else that comes in is invalid.
            sts = STS_UNEXPECTED_EVENT;
            break;
    }

   return sts;
}

static t_status processDryCycle (t_event event) {
    t_status sts;
 
    switch (event)
    {
        case EVENT_STOP:
            sts = STS_ALL_GOOD;  
            currentState = STATE_IDLE;  // Go back to the Idle State
            break;

        default:                 //  Anything else that comes in is invalid.
            sts = STS_UNEXPECTED_EVENT;
            break;
    }

   return sts;
}


//  These functions will be called to bring the dishwasher in and out of low-power mode.
//  None of the Dishwasher cycles should be performed until power is applied.

t_status applyPower ()
{
   if (currentState == STATE_IDLE)
   {
      powerOn = 1;
      return (STS_ALL_GOOD);
   }
   else
   {
      return (STS_GENERAL_ERROR);
   }
}

t_status turnOffPower ()
{
   if (currentState == STATE_IDLE)
   {
      powerOn = 0;
      return (STS_ALL_GOOD);
   }
   else
   {
      return (STS_GENERAL_ERROR);
   }
}

//
//  This function is the main entry point into the Dishwasher Finite State Machine.  This function will pass the incoming event
//  to the corresponding handler routine based on the current state of the machine.
//
t_status EventHandler (t_event event) {

   t_status ret_sts;

    switch (currentState)
    {
        case STATE_IDLE :
            ret_sts = processIdleState (event);
            break;

        case STATE_WASHING :
            ret_sts = processWashCycle (event);
            break;

        case STATE_RINSING :
            ret_sts = processRinseCycle (event);
            break;

        case STATE_DRYING :
            ret_sts = processDryCycle (event);
            break;

        default :
            ret_sts = STS_GENERAL_ERROR;  // Invalid State.  Should never happen.
            break;
    }

   return ret_sts;
}






