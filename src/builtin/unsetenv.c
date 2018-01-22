#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "mysh_builtins.h"

static void	unset_matches_in_env(char ***env, char *to_unset)
{
  t_uint	tmp;
  t_uint	idx;
  char		**env_tmp;
  char		*elem;

  idx = 0;
  env_tmp = *env;
  while (env_tmp != NULL && env_tmp[idx])
    {
      elem = my_strdup(env_tmp[idx]);
      tmp = 0;
      while (elem[tmp] && elem[tmp] != '=')
	tmp += 1;
      elem[tmp] = '\0';
      if (match(elem, to_unset) == true)
	my_unsetenv(env, elem);
      else
	idx += 1;
      free(elem);
    }
  return ;
}

t_uchar		run_unsetenv(char ***env, char **argv)
{
  t_uint	idx;

  if (count_args(argv) < 2)
    {
      my_dprintf(STDERR, "unsetenv: Too few arguments.\n");
      return (1);
    }
  idx = 1;
  while (argv[idx])
    {
      unset_matches_in_env(env, argv[idx]);
      idx += 1;
    }
  return (0);
}
