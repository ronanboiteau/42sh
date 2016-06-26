#include <stdlib.h>
#include "my.h"

t_uchar		print_builtins(char ***env, char **argv)
{
  (void)env;
  (void)argv;
  if (argv[1] != NULL)
    {
      my_dprintf(STDERR, "builtins: Too many arguments.\n");
      return (1);
    }
  my_printf("builtins" "\t" "cd" "\t" "chdir" "\t" "echo" "\t" "env" "\t"
	    "printenv" "\t" "pwd" "\t" "setenv" "\n"
	    "unsetenv" "\n");
  return (0);
}
