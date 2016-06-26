#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "mysh_run.h"

static int	find_pipes(char **command)
{
  int		idx;
  int		pipes;

  pipes = 0;
  idx = 0;
  while (command[idx])
    {
      if (my_cmp("|", command[idx]))
	++pipes;
      ++idx;
    }
  return (pipes);
}

t_uchar		run_command(t_builtin_ptr **builtins,
			    char ***env,
			    t_command *command)
{
  t_pipe	pipe;

  if (find_pipes(command->argv_tmp) == 0)
    return (subcommand(builtins, env, command, command->argv_tmp));
  else
    {
      pipe.builtins = builtins;
      pipe.env = env;
      pipe.command = command;
      return (run_pipe_command(&pipe));
    }
}
