#include "my.h"

int		my_max_int_tab(const int *tab, const t_uint size)
{
  t_uint	idx;
  int		greatest;

  idx = 0;
  greatest = tab[idx];
  while (idx < size)
    {
      if (tab[idx] > greatest)
	greatest = tab[idx];
      idx += 1;
    }
  return (greatest);
}
