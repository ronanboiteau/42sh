#include <stdlib.h>

int		my_strlen(const char *str)
{
  int		idx;

  idx = 0;
  while (str != NULL && str[idx])
    idx += 1;
  return (idx);
}
