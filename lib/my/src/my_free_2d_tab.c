#include <stdlib.h>
#include "my.h"

void		my_free_2d_tab(char **tab)
{
  t_uint	idx;

  if (tab == NULL)
    return ;
  idx = 0;
  while (tab[idx])
    {
      free(tab[idx]);
      idx += 1;
    }
  free(tab);
  return ;
}
