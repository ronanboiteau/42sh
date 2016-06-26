#include <stdlib.h>
#include "my.h"
#include "mysh_builtins.h"

t_uchar		run_printenv(char ***env, char **argv)
{
  char		*elem;
  char		*tmp;

  if (count_args(argv) < 2)
    {
      my_printenv(*env, '\n');
      return (0);
    }
  else if (count_args(argv) > 2)
    {
      my_dprintf(STDERR, "printenv: Too many arguments.\n");
      return (1);
    }
  if ((tmp = malloc(sizeof(char) * (my_strlen(argv[1]) + 2))) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  tmp = my_strncpy(tmp, argv[1], my_strlen(argv[1]));
  tmp = my_strncat(tmp, "=", 1);
  elem = my_getenv(*env, tmp);
  if (elem != NULL)
    my_printf("%s\n", elem);
  free(tmp);
  return (0);
}
