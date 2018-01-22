#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "mysh_opt_env.h"

static void	get_opt_env(char **argv, t_opt_env *options)
{
  int		idx;

  idx = 0;
  options->opt_0 = false;
  options->opt_u = false;
  while (argv != NULL && argv[idx])
    {
      if (my_cmp(argv[idx], "-0") || my_cmp(argv[idx], "--null"))
	options->opt_0 = true;
      else if (my_cmp(argv[idx], "-u"))
	{
	  options->opt_u = true;
	  options->opt_u_arg = argv[idx + 1];
	}
      idx += 1;
    }
  return ;
}

t_uchar		run_env(char ***env, char **argv)
{
  t_opt_env	options;

  get_opt_env(argv, &options);
  if (options.opt_u == true)
    {
      if (options.opt_u_arg == NULL || options.opt_u_arg[0] == '\0')
	{
	  my_dprintf(STDERR, "env: option requires an argument -- 'u'\n");
	  return (125);
	}
      else
	my_unsetenv(env, options.opt_u_arg);
    }
  if (options.opt_0 == true)
    my_printenv(*env, '\0');
  else
    my_printenv(*env, '\n');
  return (0);
}
