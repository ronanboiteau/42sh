#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "mysh_signal_parent.h"

int		g_signal;

static void	signal_catcher(int catched_signal)
{
  if (catched_signal == SIGINT)
    {
      my_dprintf(STDERR, "\n");
      if (!isatty(STDIN))
	exit(130);
    }
  g_signal = catched_signal;
  return ;
}

int		signal_handler(char mode, int sigint_behavior)
{
  int		tmp;

  if (mode == GETSIG)
    {
      tmp = g_signal;
      g_signal = 0;
      return (tmp);
    }
  if (sigint_behavior == SIGINT_IGNORE && signal(SIGINT, SIG_IGN) == SIG_ERR)
    my_exit(EXIT_FAILURE, "ERROR: Can't initiate signal handler.\n");
  else if (sigint_behavior == SIGINT_REGULAR
	   && signal(SIGINT, signal_catcher) == SIG_ERR)
    my_exit(EXIT_FAILURE, "ERROR: Can't initiate signal handler.\n");
  if (signal(SIGTERM, SIG_IGN) == SIG_ERR ||
      signal(SIGQUIT, SIG_IGN) == SIG_ERR ||
      signal(SIGTSTP, SIG_IGN) == SIG_ERR ||
      signal(SIGTTIN, SIG_IGN) == SIG_ERR ||
      signal(SIGTTOU, SIG_IGN) == SIG_ERR)
    my_exit(EXIT_FAILURE, "ERROR: Can't initiate signal handler.\n");
  return (-1);
}
