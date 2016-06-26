#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "mysh_command.h"
#include "mysh_input.h"
#include "mysh_parser.h"
#include "mysh_signal_parent.h"

static void	put_prompt(char **env, t_uchar ret)
{
  char		*user;
  char		*pwd;
  char		pwd_prefix[2];
  char		*home;

  pwd_prefix[0] = '\0';
  pwd_prefix[1] = '\0';
  user = my_getenv(env, "USER=");
  if (user == NULL || user[0] == '\0')
    user = my_getenv(env, "USERNAME=");
  pwd = my_getenv(env, "PWD=");
  home = my_getenv(env, "HOME=");
  if (my_strncmp(pwd, home, my_strlen(home)) == 0 && my_strlen(pwd) > 1)
    {
      pwd_prefix[0] = '~';
      pwd += my_strlen(home);
    }
  my_printf(GREEN "%s" RESET ":" YELLOW "%s%s\n" RESET,
	    user, pwd_prefix, pwd);
  if (ret == 0)
    my_printf("[" GREEN ":)" RESET "]");
  else
    my_printf("[" RED ":(" RESET "]");
  my_printf(" $> ");
  return ;
}

char		*get_input_raw(t_command *command, t_uchar ret, char **env)
{
  char		*input_raw;

  command->stop = false;
  command->argv = NULL;
  command->pipe_sub = NULL;
  if (isatty(STDIN))
    {
      command->interactive = true;
      put_prompt(env, ret);
    }
  else
      command->interactive = false;
  input_raw = get_next_line(STDIN);
  return (input_raw);
}

int		get_input(t_command *command,
			   t_uchar ret,
			   char **env)
{
  char		*input_raw;
  char		*input_clean;

  input_raw = get_input_raw(command, ret, env);
  if (input_raw == NULL && signal_handler(GETSIG, 0) != SIGINT)
    {
      input_clean = my_strdup("exit");
      if ((command->argv = parse_command(input_clean)) == NULL)
	return (EXIT_FAILURE);
      free(input_clean);
      return (EXIT_SUCCESS);
    }
  input_clean = my_epur_str(input_raw);
  free(input_raw);
  if (input_clean == NULL || input_clean[0] == '\0')
    {
      free(input_clean);
      return (EXIT_FAILURE);
    }
  if ((command->argv = parse_command(input_clean)) == NULL)
    return (EXIT_FAILURE);
  free(input_clean);
  command->argv_tmp = NULL;
  return (EXIT_SUCCESS);
}
