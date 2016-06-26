#include <stdlib.h>
#include "my.h"
#include "printf_flags.h"
#include "printf_puts.h"

t_uint		_print_str(int fd, t_uint printed, va_list ap)
{
  printed += my_putstr_fd(fd, va_arg(ap, const char *));
  return (printed);
}

t_uint		_str_non_printable(int fd, t_uint printed, va_list ap)
{
  t_uint	idx;
  char		*str;

  str = va_arg(ap, char *);
  idx = 0;
  if (str == NULL)
    return (printed + my_putstr_fd(fd, "(null)"));
  while (str[idx] != '\0')
    {
      if (my_char_isprintable(str[idx]))
	printed += my_putchar_fd(fd, str[idx]);
      else
	{
	  printed += my_putchar_fd(fd, '\\');
	  if (str[idx] < 64)
	    printed += my_putchar_fd(fd, '0');
	  if (str[idx] < 8)
	    printed += my_putchar_fd(fd, '0');
	  printed += my_putnbr_base_fd(fd, str[idx], "01234567");
	}
      idx = idx + 1;
    }
  return (printed);
}
