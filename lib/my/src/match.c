#include <stdbool.h>
#include <stdlib.h>
#include "my.h"

int		match(char *str1, char *str2)
{
  if (str1 == NULL || str2 == NULL)
    return (false);
  return (nmatch(str1, str2) > 0);
}
