#include "my.h"
#include "printf_flags.h"
#include "printf_puts.h"

t_uint	_convert_binary(int fd, t_uint printed, va_list ap)
{
  printed += my_putnbr_base_fd(fd, va_arg(ap, t_uint), "01");
  return (printed);
}

t_uint	_convert_decimal(int fd, t_uint printed, va_list ap)
{
  printed += my_putnbr_base_fd(fd, va_arg(ap, t_uint), "0123456789");
  return (printed);
}

t_uint	_convert_hex_lowcase(int fd, t_uint printed, va_list ap)
{
  printed += my_putnbr_base_fd(fd, va_arg(ap, t_uint), "0123456789abcdef");
  return (printed);
}

t_uint	_convert_hex_upcase(int fd, t_uint printed, va_list ap)
{
  printed += my_putnbr_base_fd(fd, va_arg(ap, t_uint), "0123456789ABCDEF");
  return (printed);
}

t_uint	_convert_octal(int fd, t_uint printed, va_list ap)
{
  printed += my_putnbr_base_fd(fd, va_arg(ap, t_uint), "01234567");
  return (printed);
}
