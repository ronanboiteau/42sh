#ifndef MYSH_RUN_H_
# define MYSH_RUN_H_

# include "mysh_builtins.h"
# include "mysh_command.h"

# define IGN (0)
# define AND (1)
# define OR (2)

typedef struct	s_pipe
{
  t_builtin_ptr	**builtins;
  char		***env;
  t_command	*command;
  int		ret;
  int		fd;
  int		pid;
  int		grandchild;
  int		pipefd[2];
}		t_pipe;

t_uchar		chck_command_logic(t_command command);
char		**get_path(char **env);
t_uchar		handle_command_logic(t_builtin_ptr **builtins,
				     char ***env,
				     t_command command);
int		redirect_input(char ***ptr, char **cmd, int fd);
int		redirect_input_double(char ***ptr, char **cmd, int fd);
int		redirect_output(char ***ptr, char **cmd, int fd, int idx);
t_uchar		run_command(t_builtin_ptr **builtins,
			    char ***env,
			    t_command *command);
t_uchar		run_pipe_command(t_pipe *pipe);
t_uchar		subcommand(t_builtin_ptr **builtins,
			   char ***env,
			   t_command *command,
			   char **to_exec);
t_uchar		search_path_and_run(char **env,
				    char **path,
				    t_command *command,
				    char **to_exec);

#endif /* !MYSH_RUN_H_ */
