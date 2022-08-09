#include "ctypes.h"
#include "database.h"

struct table_data_type Table_Data[NUMBER_OF_TABLES];

struct table_data_type Get_Table_Record(table_index_type Table)
{
  return (Table_Data[Table]);
}

void Update_Table_Record(table_index_type Table, float check_ttl, struct table_data_type Data)
{
  Table_Data[Table] = Data;
}

int log_tax_receipts( float this_tax_ttl ) {return(0);}
