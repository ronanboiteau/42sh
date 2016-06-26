#include "my.h"

char		*my_strcapitalize(char *str)
{
  t_uint	idx;

  idx = 0;
  while (str[idx] != '\0')
    {
      if (my_char_isalpha(str[idx]) == 0 || idx == 0)
	{
	  while (my_char_isalpha(str[idx]) == 0)
	    idx += 1;
	  if (my_char_islower(str[idx]))
	    str[idx] = str[idx] - 32;
	}
      idx += 1;
    }
  return (str);
}
