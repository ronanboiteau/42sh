#ifndef MYSH_BUILTINS_H_
# define MYSH_BUILTINS_H_

# include "mysh_command.h"

# define BUILTINS_NBR (9)
# define ERALPH "setenv: Variable name must contain alphanumeric characters.\n"

typedef struct	s_builtin_ptr
{
  char		*command;
  t_uchar	(*fct)(char ***env, char **argv);
}		t_builtin_ptr;

t_uchar		call_builtins(t_builtin_ptr **builtins,
			      int *builtin_found,
			      char ***env,
			      char **argv);
t_uint		count_args(char **argv);
void		free_builtins(t_builtin_ptr **builtins);
int		init_builtins(t_builtin_ptr **builtins);
t_uchar		change_directory(char ***env, char **argv);
t_uchar		print_builtins(char ***env, char **argv);
t_uchar		print_working_dir(char ***env, char **argv);
t_uchar		run_echo(char ***env, char **argv);
t_uchar		run_env(char ***env, char **argv);
t_uchar		run_exit(char **env,
			 char **path,
			 t_command *command,
			 t_builtin_ptr **builtins);
t_uchar		run_printenv(char ***env, char **argv);
t_uchar		run_setenv(char ***env, char **argv);
t_uchar		run_unsetenv(char ***env, char **argv);

#endif /* !MYSH_BUILTINS_H_ */
