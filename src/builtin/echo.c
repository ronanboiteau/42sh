#include <limits.h>
#include <stdlib.h>
#include "my.h"

static void	print_arg(char *str)
{
  int		idx;

  idx = 0;
  while (str[idx] != '\0')
    {
      my_printf("%c", str[idx]);
      ++idx;
    }
}

t_uchar		run_echo(char ***env, char **argv)
{
  t_uint	idx;
  char		option_n;

  idx = 1;
  option_n = 0;
  (void)env;
  if (argv[idx] && my_strcmp(argv[idx], "-n") == 0)
    {
      idx += 1;
      option_n = 1;
    }
  while (idx < UINT_MAX && argv != NULL && argv[idx] && argv[idx + 1])
    {
      print_arg(argv[idx]);
      my_printf(" ");
      idx += 1;
    }
  if (argv[idx])
    print_arg(argv[idx]);
  if (!option_n)
    my_printf("\n");
  return (0);
}
