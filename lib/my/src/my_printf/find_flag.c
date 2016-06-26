#include <stdlib.h>
#include "my.h"
#include "printf_flags.h"
#include "printf_puts.h"

static int	_find_extra_chars(t_cstring *str)
{
  char		extra_char;

  while (str->str[str->idx + 1] && !_char_isletter(str->str[str->idx + 1]))
    {
      if (str->str[str->idx + 1] == ' ' && extra_char != '+')
	extra_char = ' ';
      else if (str->str[str->idx + 1] == '+')
	extra_char = '+';
      str->idx += 1;
    }
  return (extra_char);
}

static t_uint	_add_extra_spaces(t_cstring *str,
				  char extra_char,
				  int fd,
				  va_list ap)
{
  va_list	ap_tmp;
  t_uint	printed;

  printed = 0;
  *ap_tmp = *ap;
  if (extra_char && (str->str[str->idx + 1] == 'i' ||
		     str->str[str->idx + 1] == 'd' ||
		     !_char_isletter(str->str[str->idx + 1])))
    {
      if ((str->str[str->idx + 1] == 'i' || str->str[str->idx + 1] == 'd')
	  && va_arg(ap_tmp, int) >= 0)
	printed += my_putchar_fd(fd, extra_char);
      else if (!_char_isletter(str->str[str->idx + 1]) && extra_char == ' ')
	printed += my_putchar_fd(fd, ' ');
    }
  return (printed);
}

const char	*_find_flag(t_cstring *str,
			    t_uint *printed,
			    int fd,
			    va_list ap)
{
  const char	*specifiers;
  char		extra_char;
  va_list	ap_tmp;

  *ap_tmp = *ap;
  specifiers = "%";
  extra_char = '\0';
  if (!_char_isletter(str->str[str->idx + 1])
      && str->str[str->idx + 1] != '%')
    {
      specifiers = str->str + str->idx + 1;
      extra_char = _find_extra_chars(str);
    }
  if (!str->str[str->idx + 1] && !_char_isletter(str->str[str->idx]))
    return (NULL);
  else
    {
      *printed += _add_extra_spaces(str, extra_char, fd, ap);
      return (specifiers);
    }
}
