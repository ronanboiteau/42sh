#include <stdlib.h>
#include "my.h"

char		**my_envcpy(char **env)
{
  t_uint	idx_line;
  char		**env_cpy;

  idx_line = 0;
  while (env != NULL && env[idx_line])
    idx_line += 1;
  if ((env_cpy = malloc(sizeof(char *) * (idx_line + 1))) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  idx_line = 0;
  while (env != NULL && env[idx_line])
    {
      env_cpy[idx_line] = my_strdup(env[idx_line]);
      idx_line += 1;
    }
  env_cpy[idx_line] = NULL;
  return (env_cpy);
}
