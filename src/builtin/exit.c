#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "mysh_command.h"
#include "mysh_builtins.h"

t_uchar		run_exit(char **env,
			 char **path,
			 t_command *command,
			 t_builtin_ptr **builtins)
{
  char		exit_status;

  if (count_args(command->argv_tmp) > 2)
    {
      my_dprintf(STDERR, "exit: Expression Syntax.\n");
      return (EXIT_FAILURE);
    }
  if (command->argv_tmp == NULL || count_args(command->argv_tmp) == 1)
    exit_status = command->last_ret;
  else if (my_str_isnum(command->argv_tmp[1]) == false)
    {
      my_dprintf(STDERR, "exit: Expression Syntax.\n");
      return (EXIT_FAILURE);
    }
  else
    exit_status = my_atoi(command->argv_tmp[1]);
  if (command->interactive == true)
    my_dprintf(STDERR, "exit\n");
  my_free_2d_tab(env);
  my_free_2d_tab(path);
  my_free_2d_tab(command->argv);
  free(command->argv_tmp);
  free_builtins(builtins);
  exit(exit_status);
  return (EXIT_SUCCESS);
}
