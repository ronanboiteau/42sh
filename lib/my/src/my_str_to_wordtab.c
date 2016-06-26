#include <stdlib.h>

static unsigned int	get_word_size(const char *str)
{
  unsigned int		size;

  size = 0;
  while (str[size] && str[size] != ' ' && str[size] != '\t')
    size += 1;
  return (size);
}

static unsigned int	count_words(const char *str)
{
  unsigned int		idx;
  unsigned int		words;

  words = 0;
  idx = 0;
  while (str[idx])
    {
      if (str[idx] == ' ' || str[idx] == '\t')
	words += 1;
      while (str[idx] == ' ' || str[idx] == '\t')
	idx += 1;
      idx += 1;
    }
  return (words + 1);
}

static char		*fill_column(const char *clean_str,
				     unsigned int *idx_str)
{
  unsigned int		idx;
  unsigned int		size;
  char			*column;

  size = get_word_size(clean_str + *idx_str);
  if (!(column = malloc(sizeof(char) * (size + 1))))
    return (NULL);
  idx = 0;
  while (idx < size && clean_str[*idx_str])
    {
      column[idx] = clean_str[*idx_str];
      *idx_str += 1;
      idx += 1;
    }
  column[idx] = '\0';
  *idx_str += 1;
  return (column);
}

char			**my_str_to_wordtab(char *clean_str)
{
  unsigned int		idx_line;
  unsigned int		idx_str;
  unsigned int		words;
  char			**tab;

  if (!clean_str)
    return (NULL);
  words = count_words(clean_str);
  if (!(tab = malloc(sizeof(char *) * (words + 1))))
    return (NULL);
  idx_str = 0;
  idx_line = 0;
  while (idx_line < words)
    {
      if (!(tab[idx_line] = fill_column(clean_str, &idx_str)))
	return (NULL);
      idx_line += 1;
    }
  tab[idx_line] = NULL;
  return (tab);
}
