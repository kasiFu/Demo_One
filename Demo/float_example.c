#include "ctypes.h"


#define LastTableIndex 3
#define FirstTableIndex 0


/*
 * Return the input value, as is.
 */
float  floatTest (float Param)
{
   return Param;
}


/*
 * Return the absolute value of the 2 input values.
 */
float floatAbsVal ( float left, float right)
{
    if (left < right)
        return(right - left);
    else
        return(left - right);
}


void floatPtrExample( float * Param)
{
   *Param *= 50;
}


struct order_type OrderArray[4];

struct order_type getOrder (int index)
{
   return OrderArray[index];
}
   
 
