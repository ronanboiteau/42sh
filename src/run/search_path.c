#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "my.h"
#include "mysh_builtins.h"
#include "mysh_exec_path.h"
#include "mysh_run.h"
#include "mysh_signal_child.h"
#include "mysh_signal_parent.h"

static int	parent_exec(pid_t pid, int *status)
{
  t_signal_ptr	**sig_handler;
  int		stop;

  stop = false;
  signal_handler(SETSIG, SIGINT_IGNORE);
  waitpid(pid, status, WUNTRACED);
  if (WIFSIGNALED(*status))
    {
      if (!(sig_handler = malloc(sizeof(t_signal_ptr *) * SIGNALS_CHILD)))
	my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
      alloc_sig_handler(sig_handler);
      init_sig_handler(sig_handler);
      if (WTERMSIG(*status) < SIGNALS_CHILD
	  && sig_handler[WTERMSIG(*status)] != NULL)
	my_dprintf(STDERR, sig_handler[WTERMSIG(*status)]->err);
      if (WTERMSIG(*status) == SIGINT)
	{
	  stop = true;
	  my_printf("\n");
	}
      free_sig_handler(sig_handler);
    }
  return (stop);
}

t_uchar		search_path_and_run(char **env,
				    char **path,
				    t_command *command,
				    char **to_exec)
{
  pid_t		pid;
  t_uchar	ret;
  char		*exec_path;
  int		status;

  status = 0;
  exec_path = get_exec_full_path(to_exec[0], path);
  if ((ret = chck_exec_path(exec_path, to_exec) == 1))
    return (ret);
  if ((pid = fork()) == (pid_t)-1)
    my_exit(EXIT_FAILURE, "ERROR: Failed to spawn child process!\n");
  if (pid == (pid_t)0)
    {
      if ((execve(exec_path, to_exec, env) == -1))
	my_exit(EXIT_FAILURE, "%s: Cannot run this file.\n", exec_path);
    }
  else if (parent_exec(pid, &status) == true)
    command->stop = true;
  signal_handler(SETSIG, SIGINT_REGULAR);
  free(exec_path);
  return (WEXITSTATUS(status));
}
