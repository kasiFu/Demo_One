#include "inlines.h"

class_with_some_inlines::class_with_some_inlines(int i)
  : m_i( i )
{
}

int class_with_some_inlines::use_int()
{
  if ( m_i )
  {
    return 3;
  }
  return 4;
}
