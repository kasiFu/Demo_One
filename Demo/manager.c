#include "ctypes.h"
#include "stdio.h"
#include "database.h"

/* Allow 10 Parties to wait */
static name_type WaitingList[10];
static unsigned int WaitingListSize = 0;
static unsigned int WaitingListIndex = 0;


const struct order_type NULL_ORDER =
      {NO_SOUP, NO_SALAD, NO_ENTREE, NO_DESSERT, NO_BEVERAGE};

/*
 *  This function adds in the tax & tip and returns a new check total
 *  It will either use the tax passed in as a user parameter, or it will
 *  use the global variable (default_tax) if it is non-zero.
 *
 */
static int log_err_cnt=0;
static float state_tax = .03;

static float default_tax = .05;

float Add_Tax_Tip( float check_total, float sales_tax, float tip )
{
    float new_total, tax;
    static int log_err;
	
    if (sales_tax < 0)
    {
        tax = sales_tax;
		tax = tax + 1;
    }
    else if (sales_tax == 0)
    {
        tax = default_tax;
    }
    else
    {
        tax = 0;
    }
    
    log_err = log_tax_receipts( tax*check_total );
    if (log_err)
    {
        log_err_cnt++;
        printf("\nError in Logging Tax Receipts\n");
    }

    new_total = check_total * (1 + tax + tip);
    return( new_total );
}


/* This function will add a free dessert to specific orders based on the 
   entree, salad, and beverage choice. */


int Add_Included_Dessert(struct order_type* Order)
{
  int rc;
  rc = 0;  //Neither

  if(Order->Entree == STEAK &&
     Order->Salad == CAESAR &&
     Order->Beverage == MIXED_DRINK)
  {
    rc = 1;
    Order->Dessert = PIE;  
  }
  else if(Order->Entree == LOBSTER &&
          Order->Salad == GREEN &&
          Order->Beverage == WINE)
  {   
    rc = 2;
    Order->Dessert = CAKE;  
  }

  return(rc);

}



float Place_Order(table_index_type Table,
                seat_index_type Seat,
                struct order_type Order)
{
  struct table_data_type Table_Data;
  struct table_data_type *Table_Bfr;


  Table_Data = Get_Table_Record(Table);

  Table_Data.Is_Occupied = v_true;
  Table_Data.Number_In_Party = Table_Data.Number_In_Party + 1;
  Table_Data.Order[Seat] = Order;

  /* Add a free dessert in some cases */
  Add_Included_Dessert(&Table_Data.Order[Seat]);
 
  switch(Order.Entree)
    {
    case NO_ENTREE : 
       break;
    case STEAK :
       Table_Data.Check_Total = Table_Data.Check_Total + COST_OF_STEAK;
       break;
    case CHICKEN :
       Table_Data.Check_Total = Table_Data.Check_Total + COST_OF_CHICKEN;
       break;
    case LOBSTER :
       Table_Data.Check_Total = Table_Data.Check_Total + COST_OF_LOBSTER;
       break;
    case PASTA :
       Table_Data.Check_Total = Table_Data.Check_Total + COST_OF_PASTA;
       break;
    default:
       printf( "Invalid Entree: %d", Order.Entree);
       break;
    }
  
  Update_Table_Record(Table, Table_Data.Check_Total, Table_Data);

  return (Table_Data.Check_Total);
}

int Clear_Table(table_index_type Table)
{
  struct table_data_type Table_Data;
  seat_index_type Seat;
  Table_Data = Get_Table_Record(Table);
  Table_Data.Is_Occupied = v_false;
  Table_Data.Number_In_Party = 1;

  printf("\nClear Table %d\n", Table);

  for (Seat=0; Seat < SEATS_AT_ONE_TABLE; Seat++)
    Table_Data.Order[Seat] = NULL_ORDER;
    Table_Data.Check_Total = 0;
 
  Update_Table_Record(Table, 0, Table_Data);
  return 0;
}

float Get_Check_Total(table_index_type Table)
{
  struct table_data_type Table_Data;
  Table_Data = Get_Table_Record(Table);
  return (Table_Data.Check_Total);
}

void Add_Party_To_Waiting_List(char* Name)
{
  int i = 0;
  if(WaitingListSize > 9)
    WaitingListSize = 0;

  while(Name && *Name) {
    WaitingList[WaitingListSize][i++] = *Name;
    Name++;
  }
  WaitingList[WaitingListSize++][i] = 0;

}

char* Get_Next_Party_To_Be_Seated(void)
{
  if(WaitingListIndex > 9)
    WaitingListIndex = 0;
  return WaitingList[WaitingListIndex++];
}


