#include "my.h"
#include "printf_flags.h"
#include "printf_puts.h"

t_uint		_print_char(int fd, t_uint printed, va_list ap)
{
  printed += my_putchar_fd(fd, va_arg(ap, int));
  return (printed);
}
