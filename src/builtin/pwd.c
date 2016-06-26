#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

t_uchar		print_working_dir(char ***env, char **argv)
{
  char		*path;

  (void)env;
  (void)argv;
  if ((path = malloc(sizeof(char) * PATH_MAX)) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! Please reduce PATH_MAX.\n");
  if (getcwd(path, 100) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: getcwd() failed.");
  my_printf("%s\n", path);
  free(path);
  return (0);
}
