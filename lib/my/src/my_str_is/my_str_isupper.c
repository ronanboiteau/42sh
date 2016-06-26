#include <stdbool.h>
#include <stdlib.h>
#include "my.h"

int		my_str_isupper(const char *str)
{
  t_uint	idx;

  if (str == NULL)
    return (false);
  idx = 0;
  while (str[idx] != '\0')
    {
      if (!(str[idx] >= 'A' && str[idx] <= 'Z'))
	return (false);
      idx += 1;
    }
  return (true);
}
