#include <stdlib.h>
#include "my.h"
#include "printf_puts.h"

int		my_showstr(int fd, const char *str)
{
  t_uint	idx;

  idx = 0;
  if (str == NULL)
    {
      my_putstr_fd(fd, "(null)");
      return (my_strlen("(null)"));
    }
  while (str[idx] != '\0')
    {
      if (my_char_isprintable(str[idx]))
	my_putchar_fd(fd, str[idx]);
      else
	{
	  my_putchar_fd(fd, '\\');
	  if (str[idx] < 16)
	    my_putchar_fd(fd, '0');
	  my_putnbr_base_fd(fd, str[idx], "0123456789abcdef");
	}
      idx += 1;
    }
  return (0);
}
