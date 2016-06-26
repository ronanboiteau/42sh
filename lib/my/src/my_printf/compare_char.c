#include <stdbool.h>
#include "my.h"
#include "printf_flags.h"

int		_char_isflag(const char letter, const t_flag *flags)
{
  int		idx;

  idx = 0;
  while (idx < FLAGS_NBR)
    {
      if (letter == flags[idx].flag_char)
	return (idx);
      idx += 1;
    }
  return (-1);
}

int		_char_isletter(const char letter)
{
  return ((letter >= 'a' && letter <= 'z') ||
	  (letter >= 'A' && letter <= 'Z') ||
	  letter == '/' || letter == '{' ||
	  letter == '\n' || letter == '%' ||
	  letter == '}' || letter == '=' ||
	  letter == ':' || letter == ',' ||
	  letter == ';' || letter == '[' ||
	  letter == ']' || letter == '(' ||
	  letter == ')' || letter == 'l');
}
