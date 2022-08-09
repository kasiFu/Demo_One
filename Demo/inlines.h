#ifndef INLINES_H
#define INLINES_H

class class_with_some_inlines
{
public:
  class_with_some_inlines(int i);
  int use_int();
  int get_int() { return m_i; }

private:
  int m_i;
};

inline int non_member_inline(void)
{
  return 1;
}

class class_with_only_inlines
{
public:
  class_with_only_inlines() {}
  int inline_member() { return 2; }
};

#endif

