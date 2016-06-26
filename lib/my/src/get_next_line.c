#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static char	*my_strdup(const char *src)
{
  int		idx;
  char		*new_str;

  idx = 0;
  while (src && src[idx])
    idx += 1;
  if (!(new_str = malloc(sizeof(char) * idx + 1)))
    return (NULL);
  idx = 0;
  while (src[idx] != '\0')
    {
      new_str[idx] = src[idx];
      idx += 1;
    }
  new_str[idx] = '\0';
  return (new_str);
}

static char	*str_cpy_cat(char *dest,
			     const char *src,
			     t_uint nbr,
			     int concatenate)
{
  t_uint	idx;
  t_uint	idx_src;

  idx = 0;
  if (concatenate == true)
    {
      while (dest != NULL && dest[idx])
	idx += 1;
      idx_src = 0;
      while (src[idx_src] && idx_src < nbr)
	{
	  dest[idx] = src[idx_src];
	  idx += 1;
	  idx_src += 1;
	}
      dest[idx] = '\0';
      return (dest);
    }
  while (src[idx] && idx < nbr)
   {
      dest[idx] = src[idx];
      idx += 1;
    }
  dest[idx] = '\0';
  return (dest);
}

static char	*auto_alloc(char *ptr, size_t mem)
{
  char		*new_ptr;
  int		ptr_len;

  ptr_len = 0;
  while (ptr && ptr[ptr_len])
    ptr_len += 1;
  if (!ptr)
    {
      if (!(new_ptr = malloc(sizeof(char) * mem)))
	return (NULL);
      if (mem > 0)
	new_ptr[0] = '\0';
      return (new_ptr);
    }
  if (!(new_ptr = malloc(sizeof(char) * (ptr_len + 1 + mem))))
    return (NULL);
  new_ptr = str_cpy_cat(new_ptr, ptr, ptr_len, false);
  free(ptr);
  return (new_ptr);
}

static char	*get_new_buffer(char *buf,
				char *buf_full,
				const int fd,
				int eols)
{
  int		tmp;

  while (true)
    {
      eols = 0;
      tmp = 0;
      while (buf_full && buf_full[tmp])
      	{
      	  if (buf_full[tmp++] == '\n')
	    eols += 1;
      	}
      if (eols != 0)
	return (buf_full);
      if ((tmp = read(fd, buf, READ_SIZE)) <= 0 || (buf[tmp] = '\0')
	  || !(buf_full = auto_alloc(buf_full, READ_SIZE + 1)))
      	{
	  if (buf_full != NULL && buf_full[0] != '\0')
	    return (buf_full);
	  free(buf);
	  free(buf_full);
      	  return (NULL);
      	}
      buf_full = str_cpy_cat(buf_full, buf, READ_SIZE, true);
    }
}

char		*get_next_line(const int fd)
{
  static char	*buffer;
  char		*buf;
  int		idx_buf;
  int		idx;
  char		*line;

  idx_buf = 0;
  if (READ_SIZE <= 0 || !(buf = malloc(sizeof(char) * (READ_SIZE + 1)))
      || !(buffer = get_new_buffer(buf, buffer, fd, 0)))
    return (NULL);
  free(buf);
  idx = 0;
  while (buffer[idx_buf + idx] && buffer[idx_buf + idx] != '\n')
    idx += 1;
  while (buffer[idx_buf + idx] && buffer[idx_buf + idx] != '\n')
    idx += 1;
  buf = buffer;
  if (!(line = auto_alloc((line = NULL), idx + 2)) ||
      !(buffer = buf[idx_buf + idx] == '\0' ? my_strdup("\0")
	: my_strdup(buf + idx_buf + idx + 1)))
    return (NULL);
  line = str_cpy_cat(line, buf + idx_buf, idx + 1, false);
  line[idx] = '\0';
  free(buf);
  return (line);
}
