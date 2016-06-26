#ifndef MYSH_SIGNAL_CHILD_H_
# define MYSH_SIGNAL_CHILD_H_

# define SIGNALS_CHILD (65)

typedef struct	s_signal_ptr
{
  int		signal;
  char		*err;
}		t_signal_ptr;

void		alloc_sig_handler(t_signal_ptr **sig_handler);
void		free_sig_handler(t_signal_ptr **sig_handler);
void		init_sig_handler(t_signal_ptr **sig_handler);

#endif /* !MYSH_SIGNAL_CHILD_H_ */
