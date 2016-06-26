#include <stdlib.h>
#include "my.h"

t_uint		count_args(char **argv)
{
  t_uint	argc;

  argc = 0;
  while (argv != NULL && argv[argc])
    argc += 1;
  return (argc);
}
