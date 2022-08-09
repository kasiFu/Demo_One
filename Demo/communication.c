#include "communication.h"

/*
 *  Copy & paste these 3 lines into User Globals:

#include "communication.h"
VCAST_USER_GLOBALS_EXTERN AltCmdT AltCmd;
VCAST_USER_GLOBALS_EXTERN CourseCmdT CourseCmd;

 */
 

/*
 *  Course Values: Floating point value in Radians
 *
 *  There are 2*Pi radians in 360 degrees:
 *    North = 0 Radians
 *    East  = Pi/2 Radians
 *    South = Pi   Radians
 *    West  = (3/2)*Pi Radians
 *    2*Pi is back to North again.
 *
 *    So, the range for the Course is between 0 & 2*Pi.
 */


#define MIN_COURSE 0
#define MAX_COURSE (2*Pi)

/*
 *  Altitude Values: Integer value between 10 & 40,000 ft.
 */
#define MIN_ALTITUDE 10
#define MAX_ALTITUDE 40000

enum Boolean ProcessMessage ( MessageT messageCategory, void *message )
{
 enum Boolean rc=True;

 switch ( messageCategory )
 {
   case Change_Altitude:
   {
      AltCmdT *cmd = (AltCmdT *)message;
      int altitude = cmd->newAltitude;

      if ( (altitude < MIN_ALTITUDE) || (altitude > MAX_ALTITUDE) )
      {
          printf("\nBad Altitude: %d\n", altitude);
          rc = False;
      }
      else
      {
         ChangeAltitude ( altitude );
         printf("\nNew Altitude: %d\n", altitude);
      }
      break;
   }

   case Change_Course:
   {
      CourseCmdT *cmd = (CourseCmdT *)message;
      float course = cmd->newCourse;

      if ( (course < MIN_COURSE) || (course > MAX_COURSE))
      {
         printf("\nBad Course: %d\n", course);
         rc = False;
      }
      else
      {
         printf ("\nNew Course: %d\n", course );
         ChangeCourse ( course );
      }
      break;
   }

   case Text_Message:
   {
      char *ascii_msg;
      ascii_msg = (char *)message;
      printf ("\n%s\n", ascii_msg );
      break;
   }

   default:  
       InvalidCommand( messageCategory );

 }

 return(rc);
}
