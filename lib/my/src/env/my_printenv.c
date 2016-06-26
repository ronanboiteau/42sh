#include <stdlib.h>
#include "my.h"

void		my_printenv(char **env, char separator)
{
  t_uint	idx;

  idx = 0;
  while (env != NULL && env[idx])
    {
      my_printf("%s%c", env[idx], separator);
      idx += 1;
    }
  return ;
}
