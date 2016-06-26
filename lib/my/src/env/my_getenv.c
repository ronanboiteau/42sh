#include <stdlib.h>
#include "my.h"

char		*my_getenv(char **env, const char *to_find)
{
  t_uint	idx;
  char		*elem;

  elem = NULL;
  idx = 0;
  while (env != NULL && env[idx])
    {
      if (!my_strncmp(env[idx], to_find, my_strlen(to_find)))
	elem = env[idx] + my_strlen(to_find);
      idx += 1;
    }
  return (elem);
}
