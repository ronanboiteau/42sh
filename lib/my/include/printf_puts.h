#ifndef PRINTF_PUTS_H_
# define PRINTF_PUTS_H_

t_uint	my_putchar(const char letter);
t_uint	my_putchar_fd(int fd, const char letter);
t_uint	my_putnbr_base_fd(int fd, t_uint nbr, const char *base);
t_uint	my_putnbr_base_ull(int fd, t_ull nbr, const char *base);
t_uint	my_putnbr_printf(int fd, int nbr);
t_uint	my_put_nbr_fd(int fd, int nbr);
t_uint	my_putstr(const char *str);
t_uint	my_putstr_fd(int fd, const char *str);
int	my_showstr(int fd, const char *str);

#endif /* !PRINTF_PUTS_H_ */
