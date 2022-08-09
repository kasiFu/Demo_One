/********************************
 *
 *  Revere Test
 *
 *********************************/

const char * revere( int lights )
{
   const char * manner = "by land";

   if( lights > 0 )

      if( lights == 2 ) manner = "by sea";

   else manner = "";
   return manner;
}


/********************************
 *
 *  Max Run - Determines the 
 *            returns the maximum 
 *            run of 0's or 1's 
 *
 *********************************/

unsigned maxr( unsigned u, unsigned len )
{
   unsigned n = 0, m;
   unsigned lowbit = u & 1;

   if( len == 0 ) return 0;
   while( (u & 1) == lowbit && n < len )
       { u >>= 1; n++; }
   m = maxr( u, len-n );
   return n > m ? n : m;
}

/* max_run(u) returns the maximum run of 0's or 1's in u */
unsigned max_run( unsigned u )
{
   unsigned word_length = 0;
   unsigned w = ~0u;
   while( w ) { word_length++; w >>= 1; }
   return maxr( u, w ); 
}

/********************************
 *
 *  My Square Root - Calculates 
 *            the square root from
 *            estimations
 *
 *********************************/

double myAbs( double x ) { return x >= 0 ? x : -x; }
double mySqrtEst( double y )
{
   double x = 1.0;             /* initial estimate */
   int error;

   if( y <= 0 ) return 0;      /* ensure positive value */
   while( myAbs( error = y - x * x ) > .0005 )
       x = x + error / (2*x);  /* adjust estimate */
   return x;
}


/********************************
 *
 *  Score Data - Scores an int
 *            for numbers of 1
 *
 *********************************/

int scoreData(unsigned word)  // returns the number of 1 bits in a word
{
   int n = 0;
   int bitCount[16] = { 0,1,2,2,1,2,2,3,1,2,2,3,2,3,4 };

   while( word > 0 )
   {
      n += bitCount[ word & 0xF ];
      word >>= 4;
   }
   return n;
}
