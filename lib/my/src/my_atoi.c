#include <limits.h>
#include "my.h"

static int	_skip_letters(const char *str)
{
  int		idx;

  idx = 0;
  while (str[idx] && str[idx] != '-' && str[idx] != '+' &&
	 (str[idx] < '0' || str[idx] > '9'))
    idx += 1;
  while ((str[idx + 1] && (str[idx + 1] == '-' || str[idx + 1] == '+'))
	 || str[idx] == '+')
    idx += 1;
  return (idx);
}

static int	_set_reverser(const char *str, int *idx)
{
  if (str[*idx] == '-')
    {
      *idx += 1;
      return (-1);
    }
  return (1);
}

int		my_atoi(const char *str)
{
  t_ll		result;
  int		reverser;
  int		idx;
  int		lenght;

  result = 0;
  idx = _skip_letters(str);
  reverser = _set_reverser(str, &idx);
  lenght = idx;
  while (str[lenght] >= '0' && str[lenght] <= '9')
    lenght += 1;
  while (idx < lenght)
    {
      result = result + (t_ll)((str[idx] - '0') *
			       my_power(10, lenght - idx - 1));
      if (result < INT_MIN || result - 1 > INT_MAX)
	return (0);
      idx += 1;
    }
  result *= reverser;
  return ((int)result);
}
