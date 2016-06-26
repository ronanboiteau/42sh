#ifndef MYSH_COMMAND_H_
# define MYSH_COMMAND_H_

typedef struct	s_command
{
  char		**argv;
  char		**argv_tmp;
  char		**pipe_sub;
  char		interactive;
  int		stop;
  unsigned char	last_ret;
}		t_command;

typedef struct	s_subcommand
{
  int		builtin_found;
  int		fd;
  int		pid;
  t_uchar	ret;
}		t_subcommand;

#endif /* !MYSH_COMMAND_H_ */
