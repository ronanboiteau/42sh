#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "my.h"
#include "mysh_exec_path.h"
#include "mysh_run.h"

static char	**get_sub(t_command *command, int *idx, int dry_run)
{
  char		**sub;
  int		idx_sub;
  int		idx_tmp;

  idx_tmp = *idx;
  if (*idx > 0 && command->argv_tmp[*idx])
    ++idx_tmp;
  idx_sub = 0;
  while (command->argv_tmp[idx_tmp + idx_sub] &&
	 !my_cmp(command->argv_tmp[idx_tmp + idx_sub], "|"))
    idx_sub += 1;
  if (!(sub = malloc(sizeof(char *) * (idx_sub + 1))))
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  idx_sub = 0;
  while (command->argv_tmp[idx_tmp] && !my_cmp(command->argv_tmp[idx_tmp], "|"))
    {
      sub[idx_sub] = command->argv_tmp[idx_tmp];
      idx_tmp += 1;
      idx_sub += 1;
    }
  sub[idx_sub] = NULL;
  if (!dry_run)
    *idx = idx_tmp;
  return (sub);
}

static int	parent(int pid, int pipefd[2], int *tmp, char **next)
{
  int		status;
  int		ret_child = 0;

  waitpid(pid, &status, WUNTRACED);
  if (!next || !next[0])
    ret_child = WEXITSTATUS(status);
  if (close(pipefd[1]) == -1)
    my_exit(EXIT_FAILURE, "ERROR: Can't close pipe.\n");
  if ((*tmp = dup(pipefd[0])) == -1)
    my_exit(EXIT_FAILURE, "ERROR: Can't duplicate fd.\n");
  if (close(pipefd[0]) == -1)
    my_exit(EXIT_FAILURE, "ERROR: Can't close pipe.\n");
  return (ret_child);
}

static int	child_exec(t_command *command, int idx, int pid)
{
  int		status;

  if (!get_sub(command, &idx, true) || !get_sub(command, &idx, true)[0])
    {
      waitpid(pid, &status, WUNTRACED);
      return (WEXITSTATUS(status));
    }
  else
    return (EXIT_SUCCESS);
}

static void	spawn_child(t_pipe *pipecf, int *idx)
{
  char		buf;

  if ((pipecf->grandchild = fork()) == (pid_t)-1)
    my_exit(EXIT_FAILURE, "ERROR: Failed to spawn child process.\n");
  if (pipecf->grandchild == (pid_t)0)
    {
      if (pipecf->fd != -1 && (dup2(pipecf->fd, STDIN) == -1 ||
			       close(pipecf->pipefd[0])))
	my_exit(EXIT_FAILURE, "ERROR: Can't get pipe output.\n");
      if (!get_sub(pipecf->command, idx, true) ||
	  !get_sub(pipecf->command, idx, true)[0])
	pipecf->ret = subcommand(pipecf->builtins, pipecf->env,
				 pipecf->command, (pipecf->command)->pipe_sub);
      else if (dup2(pipecf->pipefd[1], STDOUT) == -1)
	my_exit(EXIT_FAILURE, "ERROR: Can't write to pipe.\n");
      else
	pipecf->ret = subcommand(pipecf->builtins, pipecf->env,
				 pipecf->command, (pipecf->command)->pipe_sub);
      while (read(pipecf->fd, &buf, 1) > 0);
      if (close(pipecf->pipefd[1]) == -1)
	my_exit(EXIT_FAILURE, "ERROR: Can't close pipe.\n");
      exit(pipecf->ret);
    }
  else
    exit(child_exec(pipecf->command, *idx, pipecf->grandchild));
}

t_uchar		run_pipe_command(t_pipe *pipecf)
{
  int		idx;

  pipecf->fd = -1;
  pipecf->ret = 1;
  idx = 0;
  while (((pipecf->command->pipe_sub = get_sub(pipecf->command, &idx, false)))
	 && pipecf->command->pipe_sub[0])
    {
      if (pipe(pipecf->pipefd) == -1 || (pipecf->pid = fork()) == (pid_t)-1)
	my_exit(EXIT_FAILURE, "ERROR: Failed to create pipe.\n");
      if (pipecf->pid == (pid_t)0)
	spawn_child(pipecf, &idx);
      else
	pipecf->ret = parent(pipecf->pid, pipecf->pipefd, &pipecf->fd,
			     get_sub(pipecf->command, &idx, true));
    }
  return (pipecf->ret);
}
