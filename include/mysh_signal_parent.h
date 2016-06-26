#ifndef MYSH_SIGNAL_PARENT_H_
# define MYSH_SIGNAL_PARENT_H_

# define SETSIG (0)
# define GETSIG (1)
# define SIGINT_IGNORE (0)
# define SIGINT_REGULAR (1)

int		signal_handler(char mode, int sigint_behavior);

#endif /* !MYSH_SIGNAL_PARENT_H_ */
