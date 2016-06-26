#include <stdbool.h>
#include <stdlib.h>
#include "my.h"

int		my_str_isprintable(const char *str)
{
  t_uint	idx;

  if (str == NULL)
    return (false);
  idx = 0;
  while (str[idx] != '\0')
    {
      if (!((str[idx] >= 32 && str[idx] <= 126) || str[idx] == '\0'
	    || (str[idx] >= 7 && str[idx] <= 13)))
	return (false);
      idx += 1;
    }
  return (true);
}
