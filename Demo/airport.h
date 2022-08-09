#ifndef PRINT_H
#define PRINT_H

#include "airport_types.h"


struct LegData {
   FlightInfoT theFlight;
   float       theCost;
   };

typedef unsigned BoardingPassT;

BoardingPassT BoardingPassCreate ( char * name );

void BoardingPassAddFlight ( BoardingPassT this,
                             FlightInfoT   info,
                             float         cost );

void BoardingPassPrintAll ( BoardingPassT this );

#endif
