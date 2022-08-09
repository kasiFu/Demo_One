#include <stdio.h>
#include <string.h>
#include "ctypes.h"
#include "ctype.h"

extern int Place_Order(table_index_type Table,
                       seat_index_type Seat,
                       struct order_type Order);
extern int Clear_Table(table_index_type Table);
extern float Get_Check_Total(table_index_type Table);
extern void Add_Included_Dessert(struct order_type* Order);
extern char* Get_Next_Party_To_Be_Seated(void);
extern void Add_Party_To_Waiting_List(char *Name);

int string_to_lower(char *dest, const char *src, int max)
{
    int i=0;
    
    while (i<max)
    {
        dest[i] = (char)tolower((int)src[i]);
        if (dest[i] == '\0') break;
        i++;
    }
    return(i);  
}


int main(int argc, char *argv[])
{
  struct order_type order;
  int Total;
  int table, seat;
  char line1[100]; // Input line
  char line2[100]; // line converted to lower case
  char *name_p;
  FILE *fn;

/*
 *  If the user specifies a file name, then we'll use that as input.  Otherwise, we will use Standard Input.
 */ 
  if (argc > 2)
  {
    printf("\nToo many args: %d\n",argc);
    return(0);
  }

  if (argc == 2)
  {
    fn = fopen(argv[1], "r");
    if (fn == 0)
    {
        printf("\nCan't open file: %s", argv[1]);
        return(0);
    }      
  }
  else
  {
      fn = stdin;
  }


  while(1)
  {
      // Assume table 1, seat 1, for all operations.
      table = 1;
      seat = 1;
      
      printf("\nEnter one of the following:");
      printf("\n");
      printf("\n    > Pie (Free Pie Order)");
      printf("\n    > Cake (Free Cake Order)");
      printf("\n    > Steak (Steak Order)");
      printf("\n    > Chicken (Chicken Order)");
      printf("\n    > Lobster (Lobster Order)");
      printf("\n    > Pasta (Pasta Order)");
      printf("\n    > Get (Get Check Total)");
      printf("\n    > Clear (ClearTable)");
      printf("\n    > AddP Name (Add Person to Wait List)");
      printf("\n    > GetP (Get Person from Wait List)");
      printf("\n    > Q (Quit)\n");
      printf("\n    > ");
      
      fscanf(fn,"%s",line1);
      
      string_to_lower(line2,line1,sizeof(line2));
      
      if (strcmp(line2,"pie") == 0)
      {
		  order.Entree = STEAK;
		  order.Salad = CAESAR;
		  order.Beverage = MIXED_DRINK;
		  Place_Order(table, seat, order); 
      }
      else if (strcmp(line2,"cake") == 0)
      {
		  order.Entree = LOBSTER;
		  order.Salad = GREEN;
		  order.Beverage = WINE;
		  Place_Order(table, seat, order); 
      }
      else if (strcmp(line2,"chicken") == 0)
      {
		  order.Entree = CHICKEN;
		  Place_Order(table, seat, order);
      }
      else if (strcmp(line2,"pasta") == 0)
      {
		  order.Entree = PASTA;
		  Place_Order(table, seat, order);
      }
      else if (strcmp(line2,"steak") == 0)
      {
		  order.Entree = STEAK;
		  Place_Order(table, seat, order);
      }
      else if (strcmp(line2,"lobster") == 0)
      {
		  order.Entree = LOBSTER;
		  Place_Order(table, seat, order);
      }
      else if (strcmp(line2,"get") == 0)
      {
		  Total = Get_Check_Total(table);
		  printf("The Total is %d\n", Total);
      }
      else if (strcmp(line2,"clear") == 0)
      {
          Clear_Table(1);
		  Total = Get_Check_Total(table);
		  printf("The Total is %d\n", Total);
      }
      else if (strcmp(line2,"addp") == 0)
      {
          fscanf(fn,"%s",line1);
   		  Add_Party_To_Waiting_List(line1);
      }
      else if (strcmp(line2,"getp") == 0)
      {
   		  printf("\nGetting %s from list\n", Get_Next_Party_To_Be_Seated());
      }
      else if ((strcmp(line2,"q") == 0) || (strcmp(line2,"quit") == 0))
      {
          break;
      }
      else
      {
		  printf("Invalid Entry: %s\n", line1);
      }

  }
	  
  return 0;
}
