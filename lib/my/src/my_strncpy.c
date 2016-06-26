#include "my.h"

char		*my_strncpy(char *dest, const char *src, t_uint nbr)
{
  t_uint	idx;

  idx = 0;
  while (idx < nbr && src[idx])
    {
      dest[idx] = src[idx];
      idx += 1;
    }
  dest[idx] = '\0';
  return (dest);
}
