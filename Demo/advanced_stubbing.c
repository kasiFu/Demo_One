
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char* use_malloc( void )
{
  char* ptr = (char*)malloc( 10 );
  if ( !ptr )
  {
    return 0;
  }
  else
  {
    strcpy( ptr, "ok" );
  }
  return ptr;
}


/*****************************************************************************************************
 *  temp_monitor
 *
 *  This function reads a water temparature gauge and determines if it is freezing, boiling, or normal
 *
 *****************************************************************************************************/

typedef float (*tempurature_guage_func_ptr_t)(void);

enum e_temp_range
{
  BAD_GAUGE,
  FREEZING,
  NORMAL,
  BOILING,
};

enum e_scale
{
  CELSIUS,
  FAHRENHEIT,
};

enum e_temp_range temp_monitor( tempurature_guage_func_ptr_t func_ptr, enum e_scale scale )
{
    float current_temperature;
    enum e_temp_range rc;
    
    if ( !func_ptr )
    {
        rc = BAD_GAUGE;
    }
    else
    {       
        current_temperature = (*func_ptr)();
        
        if (scale == CELSIUS)
        {
            if (current_temperature <= 0.0)
                rc = FREEZING;
            else if (current_temperature >= 100.0)
                rc = BOILING;
            else
                rc = NORMAL;
        }
        if (scale == FAHRENHEIT)
        {
            if (current_temperature <= 32.0)
                rc = FREEZING;
            else if (current_temperature >= 212.0)
                rc = BOILING;
            else
                rc = NORMAL;
        }
    }

    return rc;

}



/*****************************************************************************************************
 *  get_numeric_string
 *
 *  This function reads a series of ASCII digits from a key pad and converts it to a number.
 *
 *****************************************************************************************************/
extern char read_key_pad(void);

#define NUMERIC(ch)     ((ch >= '0') && (ch <= '9'))
#define ALPHABETIC(ch)  ((ch >= 'A') && (ch <= 'Z'))

int get_numeric_string(int string_length)
{
    int i,val;
    char ch;
    char str[100];
	
    for (i=0; i < string_length; i++)
    {
        ch = read_key_pad();
        
        if (!NUMERIC(ch)) ch='0';

        str[i] = ch;
    }

    val = atoi(str);
    return(val);
}


/*
 *  This function prints out a log error string.  If the debug flag is on, the Time-of-day will also be included.
 *
 *  The debug flag will be returned as the return value.
 */
 
extern const int debug_flag;

int log_error_msg( char *str )
{
    static msg_num=0;
    
    time_t tod = time(NULL);

    if ( debug_flag )
    {
        printf("Log Msg #%d:  %s\n", msg_num, str);
        printf("Error Occurred on:  %s\n", ctime(&tod));
    }
    else
    {
        printf("Log Msg #%d:  %s\n", msg_num, str);
    }

    return debug_flag;
}
