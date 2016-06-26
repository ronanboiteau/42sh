#include <unistd.h>
#include "my.h"

t_uint		my_putchar_fd(int fd, const char letter)
{
  write(fd, &letter, 1);
  return (1);
}

t_uint		my_putchar(const char letter)
{
  my_putchar_fd(1, letter);
  return (1);
}
