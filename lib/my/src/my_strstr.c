#include <stdlib.h>
#include "my.h"

char		*my_strstr(char *str, const char *to_find)
{
  if (my_strlen(to_find) > my_strlen(str))
    return (NULL);
  else
    {
      if (*str == *to_find &&
	  my_strncmp(str, to_find, my_strlen(to_find)) == 0)
	return (str);
      else
	return (my_strstr(str + 1, to_find));
    }
}
