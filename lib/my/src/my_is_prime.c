#include <stdbool.h>
#include "my.h"

int		my_is_prime(const int nbr)
{
  int		idx;

  if (nbr <= 1)
    return (false);
  idx = 2;
  while (idx < nbr)
    {
      if (nbr % idx == 0)
	return (false);
      idx += 1;
    }
  return (true);
}
