
#include <stdlib.h>
#include <stdio.h>

#include "io_wrapper.h"

int close_ret = 99;


t_bool CloseFile ( struct FILE_TYPE *fp )
{
  if ( fp->isOpen )
  {
     close_ret = fclose ( (FILE *)fp->fileHandle );
     if (close_ret == 0)
         return True;
     else
         return False;
  }
  return False;
}



struct FILE_TYPE *OpenFile ( char filename[],
                             enum FileModeT mode )
{
   struct FILE_TYPE *retVal;
   retVal = (struct FILE_TYPE *)malloc(sizeof(struct FILE_TYPE));
   if (!retVal)
   {
       printf("\nNo memory available!\n");
	   return(retVal);
   }
   
   retVal->isOpen = False;
   switch ( mode )
   {
   case F_READ:
      retVal->fileHandle = (unsigned int)fopen ( filename, "r" );
      break;
   case F_WRITE:
      retVal->fileHandle = (unsigned int)fopen ( filename, "w" );
      break;
   case F_APPEND:
      retVal->fileHandle = (unsigned int)fopen ( filename, "a" );
      break;
   }

   if (retVal->fileHandle == 0)
   {
      retVal->isOpen = False;
   }
   else
   {
      retVal->isOpen = True;
   }
   
   return retVal;
}


t_bool ReadLine ( struct FILE_TYPE *fp,
               char             line[] )
{
  char *ret_ptr;

  if ( fp->isOpen )
  {
    ret_ptr = fgets ( line, 100, (FILE *)fp->fileHandle );
    if (ret_ptr == 0)
      return False;
    else
      return True;
  }
  return False;
}

t_bool WriteString ( struct FILE_TYPE *fp,
                  char             line[])
{
  int rc;

  if ( fp->isOpen )
  {
    rc = fprintf ( (FILE *)fp->fileHandle, "%s", line );
    if (rc == strlen(line))
      return True;
    else
      return False;
  }
  return False;
}

t_bool WriteInteger ( struct FILE_TYPE *fp,
                   int              value )
{
  if ( fp->isOpen )
  {
     fprintf ( (FILE *)fp->fileHandle, "%d", value );
     return True;
  }
  return False;
}

t_bool WriteFloat ( struct FILE_TYPE *fp,
                 float            value )
{
  if ( fp->isOpen )
  {
     fprintf ( (FILE *)fp->fileHandle, "%f", value );
     return True;
  }
  return False;
}

