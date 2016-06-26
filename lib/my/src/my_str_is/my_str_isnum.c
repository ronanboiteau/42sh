#include <stdbool.h>
#include <stdlib.h>
#include "my.h"

int		my_str_isnum(const char *str)
{
  t_uint	idx;

  if (str == NULL)
    return (false);
  idx = 0;
  while (str[idx])
    {
      if (!(str[idx] >= '0' && str[idx] <= '9')
	  && str[idx] != '-' && str[idx] != '+')
	return (false);
      idx += 1;
    }
  return (true);
}
