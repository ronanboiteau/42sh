#include "my.h"
#include "printf_flags.h"
#include "printf_puts.h"

t_uint	_print_int(int fd, t_uint printed, va_list ap)
{
  printed += my_putnbr_printf(fd, va_arg(ap, int));
  return (printed);
}
