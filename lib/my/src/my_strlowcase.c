#include "my.h"

char		*my_strlowcase(char *str)
{
  t_uint	idx;

  idx = 0;
  while (str[idx] != '\0')
    {
      if (str[idx] >= 'A' && str[idx] <= 'Z')
	str[idx] = str[idx] + 32;
      idx += 1;
    }
  return (str);
}
