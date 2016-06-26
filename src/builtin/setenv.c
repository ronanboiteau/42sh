#include <stdlib.h>
#include "my.h"
#include "mysh_builtins.h"

t_uchar		run_setenv(char ***env, char **argv)
{
  char		*tmp;

  if (count_args(argv) < 2)
    {
      my_printenv(*env, '\n');
      return (0);
    }
  else if (count_args(argv) > 3 || !my_str_isalpha(argv[1]) ||
	   (!my_char_islower(argv[1][0]) && !my_char_islower(argv[1][0])))
    {
      if (count_args(argv) > 3)
	my_dprintf(STDERR, "setenv: Too many arguments.\n");
      else if ((!my_char_islower(argv[1][0]) && !my_char_islower(argv[1][0])))
	my_dprintf(STDERR, "setenv: Variable name must begin with a letter.\n");
      else if (!my_str_isalpha(argv[1]))
	my_dprintf(STDERR, ERALPH);
      return (1);
    }
  if ((tmp = malloc(sizeof(char) * (my_strlen(argv[1]) + 2))) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  tmp = my_strncpy(tmp, argv[1], my_strlen(argv[1]));
  tmp = my_strncat(tmp, "=", 1);
  my_setenv(env, tmp, argv[2]);
  free(tmp);
  return (0);
}
