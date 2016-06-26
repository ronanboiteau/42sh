#include <stdbool.h>
#include <stdlib.h>
#include "my.h"

int		my_str_isalpha(const char *str)
{
  t_uint	idx;

  if (str == NULL)
    return (false);
  idx = 0;
  while (str[idx] != '\0')
    {
      if (!((str[idx] >= 'A' && str[idx] <= 'Z') ||
	    (str[idx] >= 'a' && str[idx] <= 'z') ||
	    (str[idx] >= '0' && str[idx] <= '9')))
	return (false);
      idx += 1;
    }
  return (true);
}
