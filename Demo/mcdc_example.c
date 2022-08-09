
/*
 *  This function determines if a company is open for business depending on the day/time.
 *  It returns a simple true/false value based on the input day/time.
 *  Time is in military time (i.e. 1700 equals 5pm)
 */
 
#define OPEN_TIME 800
#define CLOSE_TIME 1700

enum e_day_of_week {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY} ;

typedef enum e_day_of_week t_day_of_week;

int open_for_business(int time, t_day_of_week day)
{

  if ((time > OPEN_TIME) && (time < CLOSE_TIME) && (day != SUNDAY))
  {
    return(1);
  }
  else
  {
    return(0);
  }

}


int Conditional_Example (int a, int b, int c) {

   if (a && (b || c))
      return 1;
   else
      return 0;

}

//
//  The following functions may be of additional interest, wrt MC/DC, but are ifdef'd out for now
//

#if 0
	
int LargeConditional1 (
   int a, int b, int c, int d, 
   int e, int f, int g, int h, int i) {

   int local;

   local = (a && b && c && d && e && f && g && h && i);
   
   return local;
   
}
	
int LargeConditional2 (
   int a, int b, int c, int d, 
   int e, int f, int g, int h, int i) {

   int local;

   local = (((a || b) && !c) && (d || e) && (f != g) && h && i);
   
   return local;
   
}


/*
 *  This is a simple example to show why MC/DC is more thourough than Branch Coverage.
 *
 *  If you are doing Statement+Branch Analysis, and you insert Basis Path tests on this function,  you'll get 100% coverage
 *  and it will appear everything is good.
 *
 *  On the other hand, if you turn on Statement+MC/DC and insert MC/DC Test Cases, one of the tests will crash when you
 *  try to access the salary database with a bad Employee ID.
 */
 
#define MAX_ID 100
extern int emp_salary_db[MAX_ID];

/*
 *  Return the Salary of an employee, given either the Employee ID or the Employee's name.
 */
int get_salary(char *name, unsigned short emp_id)
{
  int salary;

  /*
   * If the Employee ID is valid, or the name is given, return the salary of this employee.
   */
  if ((emp_id < MAX_ID) || (name != 0))
  {
    salary = emp_salary_db[emp_id];
  }
  else
  {
    salary = 0;
  }

  return(salary);
}

#endif
