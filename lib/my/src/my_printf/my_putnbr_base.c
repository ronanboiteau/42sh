#include "my.h"
#include "printf_puts.h"

t_uint		my_putnbr_base_fd(int fd, t_uint nbr, const char *base)
{
  t_uint	base_int;
  t_uint	printed;

  printed = 0;
  base_int = 0;
  while (base[base_int] != '\0')
    base_int = base_int + 1;
  if (base_int < 2)
    return (0);
  if (nbr >= base_int)
    printed += my_putnbr_base_fd(fd, nbr / base_int, base);
  printed += my_putchar_fd(fd, base[nbr % base_int]);
  return (printed);
}

t_uint		my_putnbr_base_ull(int fd, t_ull nbr, const char *base)
{
  t_uint	base_int;
  t_uint	printed;

  printed = 0;
  base_int = 0;
  while (base[base_int] != '\0')
    base_int = base_int + 1;
  if (base_int < 2)
    return (0);
  if (nbr >= base_int)
    printed += my_putnbr_base_ull(fd, nbr / base_int, base);
  printed += my_putchar_fd(fd, base[nbr % base_int]);
  return (printed);
}
