
#include "stdio.h"

void door_ajar_alarm(int);

typedef enum
{
    POWER_UP, DOOR_OPEN, DOOR_CLOSED
}
t_door_state;

#define THRESHOLD 3

/*
 *  This function gets called at a periodic rate and determines the Open/Close status of a door.
 *  It uses a hysteresis/debounce algorithm to determine the stable state.  If the door status
 *  is either "opened" or "closed" for THRESHOLD subsequent times, then the state is considered stable.
 */

 t_door_state process_door_event(t_door_state current_state)
{
    static int open_count;
    static int close_count;
    static t_door_state stable_state;
    int z;

    switch (current_state)
    {
        case POWER_UP:
            open_count = 0;
            close_count = 0;
            stable_state=POWER_UP;
            break;

        case DOOR_OPEN:
            open_count++;
            close_count = 0;
            break;

        case DOOR_CLOSED:
            open_count = 0;
            close_count++;
            break;
    }

    if (open_count == THRESHOLD)
    {
        door_ajar_alarm(1);  // Set Alarm
        stable_state = DOOR_OPEN;
    }

    if (close_count == THRESHOLD)
    {
        door_ajar_alarm(0);  // Clear Alarm
        stable_state = DOOR_CLOSED;
    }
    
    return(stable_state);
    
}


/*
 *  This function simply reads a Memory Mapped Register and isolates
 *  the Receive Error Bit.
 */

#define DEVICE_REG ((unsigned char*)0x80008000)
#define RX_ERROR_BIT 0x04

int check_rx_err_bit(void)
{
  unsigned char reg_value;

  reg_value = *DEVICE_REG;

  if (reg_value & RX_ERROR_BIT)
    return(1);
  else
    return(0);
}


/*
 *  This function is a task that monitors for any Receive Errors.
 *  If an error occurs, it is counted and reported.
 */

extern void sleep1(int delay);
extern void report_error(char *);

static int rx_err_count=0;

void monitor_task(void)
{ 
    while (1)
    {
        if (check_rx_err_bit())
        {
            rx_err_count++;
            report_error("Rx Error");
        }
        
        sleep1(100);  // Sleep 100ms

    }

    return;

}


/*
 *  Example code to show some highlights of probe points.
 */

static int tank_size = 20;  // In gallons

extern float get_fuel_level(void);
extern float get_recent_mpg(void);


float miles_before_fillup(void)
{
    float fuel_level, mpg, miles;
     
    fuel_level = get_fuel_level();
    if (fuel_level > tank_size)
    {
        printf("\nInvalid Fuel Reading\n");
        fuel_level = tank_size;
    }
    
    mpg = get_recent_mpg();
    
    miles =  fuel_level*mpg;
    
    return(miles);
}
    
    
    

