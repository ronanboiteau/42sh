#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "mysh_builtins.h"
#include "mysh_input.h"
#include "mysh_run.h"
#include "mysh_signal_parent.h"

static void	chkenv(char ***env)
{
  if (my_getenv(*env, "PATH=") == NULL)
    my_setenv(env, "PATH=", "/bin:/usr/local/bin:/sbin:/usr/bin:/usr/sbin");
  return ;
}

int		main(int argc, char **argv, char **environ)
{
  t_builtin_ptr	**builtins;
  t_command	command;
  t_uchar	ret;
  char		**env;

  (void)(argc + argv);
  ret = EXIT_SUCCESS;
  env = my_envcpy(environ);
  if (!(builtins = malloc(sizeof(t_builtin_ptr *) * (BUILTINS_NBR + 1)))
      || init_builtins(builtins) == 1)
    return (EXIT_FAILURE);
  while (true)
    {
      command.last_ret = ret;
      signal_handler(SETSIG, SIGINT_REGULAR);
      chkenv(&env);
      if (!get_input(&command, ret, env)
	  && !(ret = chck_command_logic(command)))
	ret = handle_command_logic(builtins, &env, command);
      my_free_2d_tab(command.argv);
    }
  return (EXIT_SUCCESS);
}
