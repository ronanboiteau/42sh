#include <stdbool.h>
#include "my.h"

void		my_sort_int_tab(int *tab, int size)
{
  t_uint	idx;
  int		sorted;

  sorted = false;
  while (!sorted)
    {
      sorted = true;
      idx = 0;
      while (tab[idx + 1])
	{
	  if (tab[idx] > tab[idx + 1])
	    {
	      my_swap(&tab[idx], &tab[idx + 1]);
	      sorted = false;
	    }
	  idx += 1;
	}
      my_max_int_tab(tab, size);
      idx += 1;
    }
  return ;
}
