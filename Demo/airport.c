#include "airport.h"
#include <stdio.h>

static char * TranslateAirportCode ( airportCodesT code );

void printString ( char *str );
void printFloat ( float flt );
void printCR ();

const float seaLevelPressure = 30.00;

float airportBarometer (airportCodesT code);

float airportAltimeter (airportCodesT code) {
   return 1000.0 * (seaLevelPressure-airportBarometer(code));
   }

char * IntToText ( int value );
void LogBoardingPass ( BoardingPassT this, char *message );

struct BoardingPass {
   unsigned       m_numberFlights;
   float          m_totalCost;
   struct LegData m_flights[10];
   };

#define MAXIMUM_PASSES 100
static struct   BoardingPass MemoryBlock[MAXIMUM_PASSES];
static BoardingPassT         nextAvailable = 0;

BoardingPassT BoardingPassCreate ( char * name )
{
   BoardingPassT retVal = nextAvailable;
   if ( nextAvailable >= MAXIMUM_PASSES-1 )
      nextAvailable = 0;
   else
      nextAvailable++;
   MemoryBlock[retVal].m_totalCost      = 0.0;
   MemoryBlock[retVal].m_numberFlights  = 0;
   printString ( "Name: " );
   printString ( name );
   printCR();
}

void BoardingPassAddFlight ( BoardingPassT this,
                             FlightInfoT   info,
                             float         cost )
{
   MemoryBlock[this].m_flights[MemoryBlock[this].m_numberFlights].theFlight = info;
   MemoryBlock[this].m_flights[MemoryBlock[this].m_numberFlights].theCost   = cost;
   MemoryBlock[this].m_totalCost = MemoryBlock[this].m_totalCost + cost;
   MemoryBlock[this].m_numberFlights++;
}

static void BoardingPassPrintSingle ( BoardingPassT this,
                                      unsigned      index )
{
   FlightInfoT info = MemoryBlock[this].m_flights[index].theFlight;
   char workArea[1000];
   workArea[0] = 0;
   Strcat ( workArea, "From: " );
   Strcat ( workArea, TranslateAirportCode(info.from) );
   Strcat ( workArea, "   To: " );
   Strcat ( workArea, TranslateAirportCode(info.to) );
   Strcat ( workArea, "   Flight Number: " );
   Strcat ( workArea, IntToText(info.flightNumber) );
   printString ( workArea );
   LogBoardingPass ( this, workArea );
   printCR();
   printString ( "Cost of this leg: " );
   printFloat ( MemoryBlock[this].m_flights[index].theCost );
   printCR();
}

void BoardingPassPrintAll ( BoardingPassT this )
{
   int i = 0;
   while ( i < MemoryBlock[this].m_numberFlights )
      BoardingPassPrintSingle ( this, i );
   printCR();
   printString ( "Total cost of flight: " );
   printFloat ( MemoryBlock[this].m_totalCost );
   printCR();
}

static char * TranslateAirportCode ( airportCodesT code )
{
   switch ( code )
   {
      case BOS:
         return "Boston(BOS)";
         break;
      case PHI: 
         return "Philadelphia (PHI)";
         break;
      case BWI: 
         return "Baltimore(BAL)";
         break;
      case ATL: 
         return "Atlanta(ATL)";
         break;
      case MCO: 
         return "Orlando(MCO)";
         break;
   }
   return "";
}

char * IntToText ( int value ) {
   char text[10];
   sprintf ( text, "%d", value );
   return Strdup ( text );
   }

   
   
void LogBoardingPass ( BoardingPassT this, char *message )
{
   fprintf ( stdout, "Printed boarding pass %d\n", this );
   fprintf ( stdout, "  %s\n", message );
}
