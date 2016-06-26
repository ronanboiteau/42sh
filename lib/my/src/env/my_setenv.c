#include <stdlib.h>
#include "my.h"

static char	*get_new_env_line(char *to_change, char *new_value)
{
  char		*new_env_line;

  new_env_line = malloc(sizeof(char) * (my_strlen(to_change)
					+ my_strlen(new_value) + 1));
  if (new_env_line == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  new_env_line = my_strncpy(new_env_line, to_change, my_strlen(to_change));
  new_env_line = my_strncat(new_env_line, new_value, my_strlen(new_value));
  return (new_env_line);
}

static char	**add_var(char **env,
			  char *to_change,
			  char *new_value,
			  t_uint env_size)
{
  t_uint	idx;
  char		**new_env;

  if ((new_env = malloc(sizeof(char *) * (env_size + 2))) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  idx = 0;
  while (env != NULL && env[idx])
    {
      new_env[idx] = env[idx];
      idx += 1;
    }
  new_env[idx] = malloc(sizeof(char) * (my_strlen(to_change)
					+ my_strlen(new_value) + 1));
  if (new_env[idx] == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  new_env[idx] = my_strncpy(new_env[idx], to_change, my_strlen(to_change));
  new_env[idx] = my_strncat(new_env[idx], new_value, my_strlen(new_value));
  idx += 1;
  new_env[idx] = NULL;
  free(env);
  return (new_env);
}

void		my_setenv(char ***env, char *to_change, char *new_value)
{
  t_uint	idx;
  char		*tmp;
  char		**new_env;

  new_env = *env;
  idx = 0;
  while (new_env != NULL && new_env[idx])
    {
      if (my_strncmp(new_env[idx], to_change, my_strlen(to_change)) == 0)
	{
	  tmp = get_new_env_line(to_change, new_value);
	  free(new_env[idx]);
	  new_env[idx] = my_strdup(tmp);
	  free(tmp);
	  return ;
	}
      idx += 1;
    }
  *env = add_var(new_env, to_change, new_value, idx);
  return ;
}
