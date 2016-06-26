#include <stdlib.h>
#include <signal.h>
#include "my.h"
#include "mysh_builtins.h"
#include "mysh_parser.h"
#include "mysh_run.h"
#include "mysh_signal_parent.h"

static int	get_mode(char *separator)
{
  if (my_cmp(separator, "&&"))
    return (AND);
  else if (my_cmp(separator, "||"))
    return (OR);
  return (IGN);
}

static char	**get_argv_tmp(char **argv, int *idx)
{
  int		idx_tmp;
  char		**argv_tmp;

  if (!(argv_tmp = malloc(sizeof(char *) * (count_args(argv) + 1))))
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  if (*idx > 0 && argv[*idx] != NULL)
    *idx += 1;
  idx_tmp = 0;
  while (argv[*idx] && !my_cmp(argv[*idx], ";") && !my_cmp(argv[*idx], "&&")
	 && !my_cmp(argv[*idx], "||"))
    {
      argv_tmp[idx_tmp] = argv[*idx];
      *idx += 1;
      idx_tmp += 1;
    }
  argv_tmp[idx_tmp] = NULL;
  return (argv_tmp);
}

t_uchar		handle_command_logic(t_builtin_ptr **builtins,
				     char ***env,
				     t_command command)
{
  t_uchar	ret;
  int		idx_argv;
  int		mode;

  idx_argv = 0;
  mode = IGN;
  while ((command.argv_tmp = get_argv_tmp(command.argv, &idx_argv))
	 && command.argv_tmp[0] != NULL && !command.stop)
    {
      if (mode == IGN || (ret == 0 && mode == AND)
	  || (ret != 0 && mode == OR))
	ret = run_command(builtins, env, &command);
      mode = get_mode(command.argv[idx_argv]);
      free(command.argv_tmp);
    }
  free(command.argv_tmp);
  return (ret);
}

static char	**chck_get_argv_tmp(t_command *command, int *idx)
{
  int		idx_tmp;
  char		**argv_tmp;

  if (!(argv_tmp = malloc(sizeof(char *) * (count_args(command->argv) + 1))))
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  idx_tmp = 0;
  while (command->argv[*idx] && !is_separator(command->argv[*idx]))
    {
      argv_tmp[idx_tmp] = command->argv[*idx];
      *idx += 1;
      idx_tmp += 1;
    }
  argv_tmp[idx_tmp] = NULL;
  return (argv_tmp);
}

t_uchar		chck_command_logic(t_command command)
{
  int		idx;

  idx = 0;
  while (command.argv[idx])
    {
      if (idx > 0)
	idx += 1;
      command.argv_tmp = chck_get_argv_tmp(&command, &idx);
      if (command.argv_tmp[0] == NULL)
	{
	  free(command.argv_tmp);
	  my_dprintf(STDERR, "Invalid null command.\n");
	  return (EXIT_FAILURE);
	}
      free(command.argv_tmp);
    }
  return (EXIT_SUCCESS);
}
