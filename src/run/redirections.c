#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "my.h"
#include "mysh_builtins.h"
#include "mysh_command.h"
#include "mysh_run.h"

static char	**remove_elem(char **cmd, int pos)
{
  while (cmd[pos])
    {
      cmd[pos] = cmd[pos + 1];
      ++pos;
    }
  return (cmd);
}

int		redirect_input(char ***ptr, char **cmd, int fd)
{
  int		idx;

  idx = 0;
  while (cmd[idx])
    {
      if (my_cmp(cmd[idx], "<") && cmd[idx + 1])
	{
	  if (fd != 0 || ((fd = open(cmd[idx + 1], O_RDONLY)) == -1)
	      || dup2(fd, STDIN) == -1)
	    {
	      if (fd == -1)
		my_dprintf(STDERR, "%s: No such file or directory.\n",
			   cmd[idx + 1]);
	      else
		my_dprintf(STDERR, "Ambiguous input redirect.\n");
	      return (-1);
	    }
	  *ptr = remove_elem(cmd, idx);
	  *ptr = remove_elem(cmd, idx);
	}
      ++idx;
    }
  return (fd);
}

int		redirect_output(char ***ptr, char **cmd, int fd, int idx)
{
  while (cmd[idx])
    {
      if ((my_cmp(cmd[idx], ">") || my_cmp(cmd[idx], ">>")) && cmd[idx + 1])
	{
	  if (fd != 0 || ((fd = open(cmd[idx + 1],
				     (my_cmp(cmd[idx], ">>") ? O_CREAT |
				      O_APPEND : O_CREAT) | O_WRONLY, S_IRUSR |
				     S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	      || dup2(fd, STDOUT) == -1)
	    {
	      if (fd == -1)
		my_dprintf(STDERR, "%s: No such file or directory.\n",
			   cmd[idx + 1]);
	      else
		my_dprintf(STDERR, "Ambiguous input redirect.\n");
	      return (-1);
	    }
	  *ptr = remove_elem(cmd, idx);
	  *ptr = remove_elem(cmd, idx);
	}
      ++idx;
    }
  return (fd);
}

static int	get_input_double(char *stop_str)
{
  int		fd;
  char		*input;

  if ((fd = open("/tmp/mysh_tmp7y32g", O_CREAT | O_WRONLY,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return (1);
  while ((input = get_next_line(STDIN)) && !my_cmp(input, stop_str))
    my_dprintf(fd, "%s\n", input);
  if (close(fd) == -1)
    return (1);
  if ((fd = open("/tmp/mysh_tmp7y32g", O_RDONLY)) == -1)
    return (1);
  return ((dup2(fd, STDIN)) == -1 || close(fd) == -1 ? 1 : 0);
}

int		redirect_input_double(char ***ptr, char **cmd, int fd)
{
  int		idx;

  idx = 0;
  while (cmd[idx])
    {
      if (my_cmp(cmd[idx], "<<") && cmd[idx + 1])
	{
	  if (fd)
	    {
	      my_dprintf(STDERR, "Ambiguous input redirect.\n");
	      return (-1);
	    }
	  if (get_input_double(cmd[idx + 1]))
	    {
	      my_dprintf(STDERR, "FATAL ERR! Cannot create temparary file.\n");
	      return (-1);
	    }
	  *ptr = remove_elem(cmd, idx);
	  *ptr = remove_elem(cmd, idx);
	}
      ++idx;
    }
  return (fd);
}
