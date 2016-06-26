#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

static void	update_env(char ***env, char *oldpwd)
{
  char		*pwd;

  if ((pwd = malloc(sizeof(char) * PATH_MAX)) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! Please reduce PATH_MAX.\n");
  if (getcwd(pwd, 100) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: getcwd() failed.");
  if (my_cmp(pwd, oldpwd) == false)
    my_setenv(env, "OLDPWD=", oldpwd);
  my_setenv(env, "PWD=", pwd);
  free(pwd);
  return ;
}

static t_uchar	handle_oldpwd(char **env)
{
  t_uchar	ret;
  char		*oldpwd_var;

  ret = EXIT_SUCCESS;
  oldpwd_var = my_getenv(env, "OLDPWD=");
  if (oldpwd_var == NULL)
    {
      my_dprintf(STDERR, "cd: No $OLDPWD variable set.\n");
      ret = EXIT_FAILURE;
    }
  else if (chdir(oldpwd_var) == -1)
    {
      my_dprintf(STDERR, "%s: No such file or directory.\n",
		 my_getenv(env, "OLDPWD="));
      ret = EXIT_FAILURE;
    }
  return (ret);
}

static t_uchar	switch_to_dir(char *dir)
{
  if (chdir(dir) == -1)
    {
      if (access(dir, X_OK) == -1)
	my_dprintf(STDERR, "%s: Permission denied.\n", dir);
      else
	my_dprintf(STDERR, "%s: No such file or directory.\n", dir);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static int	chk_cd_args(char **argv)
{
  if (!argv[1])
    return (0);
  if (argv[2])
    {
      my_dprintf(STDERR, "cd: Too many arguments.\n");
      return (1);
    }
  return (0);
}

t_uchar		change_directory(char ***env, char **argv)
{
  t_uchar	ret;
  char		*homedir;
  char		*oldpwd;

  ret = EXIT_FAILURE;
  if (chk_cd_args(argv))
    return (ret);
  if ((oldpwd = malloc(sizeof(char) * PATH_MAX)) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! Please reduce PATH_MAX.\n");
  if (getcwd(oldpwd, 100) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: getcwd() failed.");
  if (argv[1] == NULL)
    {
      if ((homedir = my_getenv(*env, "HOME=")) == NULL || homedir[0] == '\0')
	my_dprintf(STDERR, "cd: No $HOME variable set.\n");
      else
	ret = switch_to_dir(homedir);
    }
  else if (argv[1][0] == '-')
    ret = handle_oldpwd(*env);
  else
    ret = switch_to_dir(argv[1]);
  update_env(env, oldpwd);
  free(oldpwd);
  return (ret);
}
