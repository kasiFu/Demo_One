#ifndef IO_WRAPPER_H
#define IO_WRAPPER_H

enum bool {False, True};
typedef enum bool t_bool;

typedef unsigned int t_file_handle;

struct FILE_TYPE {
   t_file_handle fileHandle;
   t_bool  isOpen;
   };


enum FileModeT { F_READ, F_WRITE, F_APPEND };

struct FILE_TYPE *OpenFile ( char filename[],
                             enum FileModeT mode );
t_bool CloseFile ( struct FILE_TYPE *fp );

t_bool ReadLine ( struct FILE_TYPE *fp,
               char             line[] );
t_bool WriteString ( struct FILE_TYPE *fp,
                  char             line[] );
t_bool WriteInteger ( struct FILE_TYPE *fp,
                   int              value );
t_bool WriteFloat ( struct FILE_TYPE *fp,
                 float            value );

#endif
