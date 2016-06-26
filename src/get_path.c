#include <stdlib.h>
#include <unistd.h>
#include "my.h"

static int	count_dots(char *path_str)
{
  int		idx;
  int		dots;

  dots = 0;
  idx = 0;
  while (path_str[idx])
    {
      if (path_str[idx] == ':')
	dots += 1;
      idx += 1;
    }
  return (dots + 1);
}

static int	dir_size(char *path_str, int idx)
{
  int		size;

  size = 0;
  while (path_str[idx] && path_str[idx] != ':')
    {
      size += 1;
      idx += 1;
    }
  return (size);
}

static char	*get_column(char *path_str, int *idx_str)
{
  char		*column;
  int		idx_col;
  int		size;

  size = dir_size(path_str, *idx_str);
  if ((column = malloc(sizeof(char) * (size + 1))) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  idx_col = 0;
  while (idx_col < size)
    {
      column[idx_col] = path_str[*idx_str];
      *idx_str += 1;
      idx_col += 1;
    }
  column[idx_col] = '\0';
  *idx_str += 1;
  if (access(column, X_OK) == -1)
    {
      free(column);
      return (NULL);
    }
  return (column);
}

char		**get_path(char **env)
{
  char		*path_str;
  char		**path_tab;
  int		dots;
  int		idx_line;
  int		idx_str;

  path_str = my_getenv(env, "PATH=");
  dots = count_dots(path_str);
  if ((path_tab = malloc(sizeof(char *) * (dots + 1))) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  idx_str = 0;
  idx_line = 0;
  while (idx_line < dots)
    {
      if ((path_tab[idx_line] = get_column(path_str, &idx_str)) == NULL)
	dots -= 1;
      else
	idx_line += 1;
    }
  path_tab[idx_line] = NULL;
  return (path_tab);
}
