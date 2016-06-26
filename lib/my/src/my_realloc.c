#include "my.h"
#include <stdlib.h>

char		*my_realloc(char *str, int to_add)
{
  char		*new_str;
  int		new_size;

  new_size = 1;
  while (str[new_size - 1])
    new_size++;
  new_size += to_add;
  if ((new_str = malloc(sizeof(char) * (new_size + 2))) == NULL)
    my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
  new_str = my_strncpy(new_str, str, my_strlen(str));
  free(str);
  return (new_str);
}
