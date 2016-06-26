#ifndef PRINTF_FLAGS_H_
# define PRINTF_FLAGS_H_

# include <stdarg.h>
# include "string.h"
# include "my.h"

# define FLAGS_NBR (12)

typedef struct	s_flag
{
  t_uint	(*fct)(int fd, t_uint printed, va_list ap);
  char		flag_char;
}		t_flag;

typedef struct	s_cstring
{
  const char	*str;
  unsigned int	idx;
}		t_cstring;

int		_char_isflag(const char letter, const t_flag *flags);
int		_char_isletter(const char letter);
t_uint		_print_char(int fd, t_uint printed, va_list ap);
t_uint		_print_str(int fd, t_uint printed, va_list ap);
t_uint		_str_non_printable(int fd, t_uint printed, va_list ap);
t_uint		_print_int(int fd, t_uint printed, va_list ap);
t_uint		_convert_binary(int fd, t_uint printed, va_list ap);
t_uint		_convert_decimal(int fd, t_uint printed, va_list ap);
t_uint		_convert_hex_lowcase(int fd, t_uint printed, va_list ap);
t_uint		_convert_hex_upcase(int fd, t_uint printed, va_list ap);
t_uint		_convert_octal(int fd, t_uint printed, va_list ap);
t_uint		_ptr_to_hex(int fd, t_uint printed, va_list ap);
t_uint		_ptr_printed_chars(int fd, t_uint printed, va_list ap);
t_uint		_double_decimal(int fd, t_uint printed, va_list ap);
int		_init_flag(char flag_char,
			   t_uint (*fct)(int fd,
					 t_uint printed,
					 va_list ap),
			   t_flag *flags);
void		_init_structures(t_flag *flags,
				 t_cstring *str,
				 const char *format);
const char	*_find_flag(t_cstring *str,
			    t_uint *printed,
			    int fd,
			    va_list ap);

#endif /* !PRINTF_FLAGS_H_ */
