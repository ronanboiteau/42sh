#include <stdlib.h>
#include "my.h"

static t_uint	get_var_pos(char **env, char *to_unset)
{
  t_uint	pos;

  pos = 0;
  while (env != NULL && env[pos])
    {
      if (my_strncmp(env[pos], to_unset, my_strlen(to_unset)) == 0)
	return (pos);
      pos += 1;
    }
  return (pos);
}

void		my_unsetenv(char ***env, char *to_unset)
{
  t_uint	idx;
  t_uint	to_unset_pos;
  char		**new_env;

  new_env = *env;
  to_unset_pos = get_var_pos(new_env, to_unset);
  if (my_getenv(new_env, to_unset) == NULL)
    return ;
  idx = 0;
  while (new_env[idx] && idx != to_unset_pos)
    idx += 1;
  while (new_env[idx])
    {
      free(new_env[idx]);
      new_env[idx] = my_strdup(new_env[idx + 1]);
      idx += 1;
    }
  new_env[idx] = NULL;
  return ;
}
