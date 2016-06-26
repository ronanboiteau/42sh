#include <stdbool.h>
#include <stdlib.h>

static unsigned int	get_clean_str_size(const char *str)
{
  unsigned int		size;
  unsigned int		idx;

  idx = 0;
  size = 0;
  while (str[size])
    {
      if (str[idx] == ' ' || str[idx] == '\t')
	{
	  size += 1;
	  while (str[idx] == ' ' || str[idx] == '\t')
	    idx += 1;
	}
      size += 1;
    }
  return (size);
}

static unsigned int	is_last(const char *str)
{
  unsigned int		idx;

  idx = 0;
  while (str[idx])
    {
      if (str[idx] != ' ' && str[idx] != '\t')
	return (false);
      idx += 1;
    }
  return (true);
}

static char		get_char(const char *str,
				 int *first,
				 unsigned int *idx,
				 unsigned int *idx_str)
{
  char			new_letter;

  *first = false;
  new_letter = str[*idx_str];
  *idx += 1;
  *idx_str += 1;
  return (new_letter);
}

static char		*init_variables(const char *str,
					unsigned int *idx,
					unsigned int *idx_str,
					int *first)
{
  char			*clean_str;

  *first = true;
  clean_str = malloc(sizeof(char) * (get_clean_str_size(str) + 1));
  if (!clean_str)
    return (NULL);
  *idx = 0;
  *idx_str = 0;
  return (clean_str);
}

char			*my_epur_str(char *str)
{
  unsigned int		idx_str;
  unsigned int		idx;
  char			*clean_str;
  int			first;

  if (!str || !(clean_str = init_variables(str, &idx, &idx_str, &first)))
    return (NULL);
  while (str[idx_str])
    {
      if (str[idx_str] == ' ' || str[idx_str] == '\t')
	{
	  if (first == false && is_last(str + idx_str) == false)
	    {
	      clean_str[idx] = ' ';
	      idx += 1;
	    }
	  while (str[idx_str] == ' ' || str[idx_str] == '\t')
	    idx_str += 1;
	}
      else
	clean_str[idx] = get_char(str, &first, &idx, &idx_str);
    }
  clean_str[idx] = '\0';
  return (clean_str);
}
