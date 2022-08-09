#ifndef TYPES_H
#define TYPES_H

#define True  1
#define False 0

#ifndef NO_STRINGS
#include <string.h>
#define Strcpy strcpy
#define Strdup strdup
#define Strcat strcat
#define Strlen strlen
#define Strcmp strcmp
#else
char *Strcpy ( char *dst, const char *src );
char *Strdup ( const char *s1 );
char *Strcat ( char *dst, const char *src );
int   Strlen ( const char *s );
int   Strcmp ( const char *s1, const char *s2 );
#endif


#ifndef NO_MALLOC
#include <stdlib.h>
#define Malloc malloc
#define Free free
#else
void *Malloc ( unsigned size );
void Free ( void *ptr );
#endif

#ifndef NULL
#define NULL 0
#endif

enum airportCodes { BOS, PHI, BWI, ATL, MCO, MIA=200, INVALID_AIRPORT };
typedef enum airportCodes airportCodesT;
enum fareCodes { ECONOMY, BUSINESS, FIRST, INVALID_FARE };
typedef enum fareCodes fareCodesT;

struct FlightInfo { 
   airportCodesT from;
   airportCodesT to;
   unsigned      flightNumber;
   };
typedef struct FlightInfo FlightInfoT;

#endif
