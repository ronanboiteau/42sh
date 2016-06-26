#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "my.h"

static char	*get_exec_dir(char *input, char **path)
{
  DIR		*dirp;
  struct dirent	*file;
  int		idx;
  char		*exec_dir;

  exec_dir = NULL;
  idx = 0;
  while (path != NULL && path[idx])
    {
      if ((dirp = opendir(path[idx])) != NULL)
	{
	  while ((file = readdir(dirp)) != NULL)
	    {
	      if (my_cmp(input, file->d_name))
		exec_dir = path[idx];
	    }
	  if (closedir(dirp) == -1)
	    my_exit(EXIT_FAILURE, "ERROR: closedir() failed.\n");
	}
      idx += 1;
    }
  return (exec_dir);
}

char		*get_exec_full_path(char *input, char **path)
{
  char		*exec_dir;
  char		*exec_path;

  exec_dir = get_exec_dir(input, path);
  if (exec_dir != NULL)
    {
      exec_path = malloc(sizeof(char) * (my_strlen(exec_dir)
					 + my_strlen(input) + 2));
      if (exec_path == NULL)
	my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
      exec_path = my_strncpy(exec_path, exec_dir, my_strlen(exec_dir));
      exec_path = my_strncat(exec_path, "/", 1);
      exec_path = my_strncat(exec_path, input, my_strlen(input));
      return (exec_path);
    }
  else
    return (my_strdup(input));
}

t_uchar		chck_exec_path(char *exec_path, char **argv)
{
  struct stat	file_data;

  if (exec_path == NULL || access(exec_path, F_OK) == -1)
    {
      free(exec_path);
      my_dprintf(STDERR, "%S: Command not found.\n", argv[0]);
      return (1);
    }
  if (stat(exec_path, &file_data) == -1)
    my_exit(EXIT_FAILURE, "ERROR: stat() failed!\n");
  if (!S_ISREG(file_data.st_mode))
    {
      free(exec_path);
      my_dprintf(STDERR, "%S: Command not found.\n", argv[0]);
      return (1);
    }
  if (access(exec_path, X_OK) == -1)
    {
      my_dprintf(STDERR, "%s: Command not found.\n", exec_path);
      free(exec_path);
      return (1);
    }
  return (0);
}
