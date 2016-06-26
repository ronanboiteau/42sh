#include "my.h"

int		my_find_prime_sup(int nbr)
{
  while (my_is_prime(nbr) != 1)
    nbr += 1;
  return (nbr);
}
