#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "my.h"
#include "mysh_builtins.h"
#include "mysh_command.h"
#include "mysh_run.h"

static void	flush_and_exit(const int fd, const int ret)
{
  char		buf;

  if (fd)
    {
      while (read(fd, &buf, 1) > 0);
      close(fd);
    }
  exit(ret);
}

static t_uchar	parent_exec(char **path, char *command, const int pid)
{
  int		status;

  my_free_2d_tab(path);
  waitpid(pid, &status, WUNTRACED);
  if (my_cmp(command, "exit"))
    exit(WEXITSTATUS(status));
  return (WEXITSTATUS(status));
}

t_uchar		subcommand(t_builtin_ptr **builtins,
			   char ***env,
			   t_command *command,
			   char **to_exec)
{
  char		**path;
  t_subcommand	cmd;

  path = get_path(*env);
  cmd.ret = call_builtins(builtins, &cmd.builtin_found, env, to_exec);
  if (cmd.builtin_found == false && my_cmp(to_exec[0], "exit"))
    {
      cmd.builtin_found = true;
      cmd.ret = run_exit(*env, path, command, builtins);
    }
  if ((cmd.pid = fork()) == (pid_t)-1)
    my_exit(EXIT_FAILURE, "ERROR: Failed to spawn child process.\n");
  if (cmd.pid == (pid_t)0)
    {
      if ((cmd.fd = redirect_input(&to_exec, to_exec, 0)) == -1
	  || redirect_input_double(&to_exec, to_exec, cmd.ret) == -1
	  || redirect_output(&to_exec, to_exec, 0, 0) == -1)
	exit(1);
      if (cmd.builtin_found == false)
	cmd.ret = search_path_and_run(*env, path, command, to_exec);
      flush_and_exit(cmd.fd, cmd.ret);
    }
  return (parent_exec(path, to_exec[0], cmd.pid));
}
