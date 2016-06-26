#include <stdlib.h>
#include "my.h"

char		*is_separator(char *str)
{
  char		*separators[9];
  int		idx;

  separators[0] = ">>";
  separators[1] = "<<";
  separators[2] = "&&";
  separators[3] = "||";
  separators[4] = ";";
  separators[5] = ">";
  separators[6] = "<";
  separators[7] = "|";
  separators[8] = " ";
  idx = 0;
  while (idx < 9)
    {
      if (!my_strncmp(separators[idx], str, my_strlen(separators[idx])))
	return (separators[idx]);
      ++idx;
    }
  return (NULL);
}

static char		*fill_line(char *str, int *idx)
{
  char		*line;
  int		col;

  col = 0;
  while (str[*idx + col] && !is_separator(str + *idx + col))
    ++col;
  if (!(line = malloc(sizeof(char *) * (col + 1))))
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  col = 0;
  while (str[*idx] && !is_separator(str + *idx))
    {
      line[col] = str[*idx];
      *idx += 1;
      ++col;
    }
  while (str[*idx] && (str[*idx] == ' ' || str[*idx] == '\t'))
    *idx += 1;
  line[col] = '\0';
  return (line);
}

static char	**realloc_tab(char **old_tab, int size)
{
  char		**tab;
  int		idx;

  if (!(tab = malloc(sizeof(char *) * size)))
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  idx = 0;
  while (old_tab[idx])
    {
      tab[idx] = old_tab[idx];
      ++idx;
    }
  tab[idx] = NULL;
  free(old_tab);
  return (tab);
}

static char	*get_next_arg(char *tmp, char *str, int *idx)
{
  *idx += my_strlen(tmp);
  while (str[*idx] && (str[*idx] == ' ' || str[*idx] == '\t'))
    *idx += 1;
  return (my_strdup(tmp));
}

char		**parse_command(char *str)
{
  int		idx;
  int		line;
  char		**tab;
  char		*tmp;

  if (str == NULL)
    return (NULL);
  if (!(tab = malloc(sizeof(char *) * 10)))
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  idx = 0;
  line = 0;
  while (str[idx])
    {
      if ((line + 1) % 10 == 0)
	tab = realloc_tab(tab, line + 1 + 10);
      if ((tmp = is_separator(str + idx)))
	tab[line] = get_next_arg(tmp, str, &idx);
      else
	tab[line] = fill_line(str, &idx);
      ++line;
      tab[line] = NULL;
    }
  return (tab);
}
