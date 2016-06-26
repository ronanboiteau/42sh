#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"
#include "mysh_signal_child.h"

void		free_sig_handler(t_signal_ptr **sig_handler)
{
  int		idx;

  idx = 1;
  while (idx < SIGNALS_CHILD)
    {
      free(sig_handler[idx]);
      idx += 1;
    }
  free(sig_handler);
  return ;
}

void		alloc_sig_handler(t_signal_ptr **sig_handler){

  int		idx;

  idx = 1;
  while (idx < SIGNALS_CHILD)
    {
      if ((sig_handler[idx] = malloc(sizeof(t_signal_ptr) * 1)) == NULL)
	my_exit(EXIT_FAILURE, "ERROR: Out of memory! malloc() failed\n");
      idx += 1;
    }
  return ;
}

static void	init_sig_handler_3(t_signal_ptr **sig)
{
  sig[48]->err = "Signal 48\n";
  sig[49]->err = "Signal 49\n";
  sig[50]->err = "Signal 50\n";
  sig[51]->err = "Signal 51\n";
  sig[52]->err = "Signal 52\n";
  sig[53]->err = "Signal 53\n";
  sig[54]->err = "Signal 54\n";
  sig[55]->err = "Signal 55\n";
  sig[56]->err = "Signal 56\n";
  sig[57]->err = "Signal 57\n";
  sig[58]->err = "Signal 58\n";
  sig[59]->err = "Signal 59\n";
  sig[60]->err = "Signal 60\n";
  sig[61]->err = "Signal 61\n";
  sig[62]->err = "Signal 62\n";
  sig[63]->err = "Signal 63\n";
  sig[64]->err = "Signal 64\n";
  return ;
}

static void	init_sig_handler_2(t_signal_ptr **sig)
{
  sig[24]->err = "Cputime limit exceeded\n";
  sig[25]->err = "Filesize limit exceeded\n";
  sig[26]->err = "Virtual time alarm\n";
  sig[27]->err = "Profiling time alarm\n";
  sig[28]->err = "\0";
  sig[29]->err = "Pollable event occured\n";
  sig[30]->err = "Power failure\n";
  sig[31]->err = "Bad system call\n";
  sig[32]->err = "Signal 32\n";
  sig[33]->err = "Signal 33\n";
  sig[34]->err = "First Realtime Signal\n";
  sig[35]->err = "Second Realtime Signal\n";
  sig[36]->err = "Third Realtime Signal\n";
  sig[37]->err = "Fourth Realtime Signal\n";
  sig[38]->err = "Signal 38\n";
  sig[39]->err = "Signal 39\n";
  sig[40]->err = "Signal 40\n";
  sig[41]->err = "Signal 41\n";
  sig[42]->err = "Signal 42\n";
  sig[43]->err = "Signal 43\n";
  sig[44]->err = "Signal 44\n";
  sig[45]->err = "Signal 45\n";
  sig[46]->err = "Signal 46\n";
  sig[47]->err = "Signal 47\n";
  init_sig_handler_3(sig);
}

void		init_sig_handler(t_signal_ptr **sig)
{
  sig[1]->err = "Hangup\n";
  sig[2]->err = "\0";
  sig[3]->err = "Quit\n";
  sig[4]->err = "Illegal instruction\n";
  sig[5]->err = "Trace/BPT trap\n";
  sig[6]->err = "Abort\n";
  sig[7]->err = "Bus error\n";
  sig[8]->err = "Floating exception\n";
  sig[9]->err = "Killed\n";
  sig[10]->err = "User signal 1\n";
  sig[11]->err = "Segmentation fault\n";
  sig[12]->err = "User signal 2\n";
  sig[13]->err = "Broken pipe\n";
  sig[14]->err = "Alarm clock\n";
  sig[15]->err = "Terminated\n";
  sig[16]->err = "Stack limit exceeded\n";
  sig[17]->err = "\0";
  sig[18]->err = "\0";
  sig[19]->err = "\0";
  sig[19]->err = "\0";
  sig[20]->err = "\0";
  sig[21]->err = "\0";
  sig[22]->err = "\0";
  sig[23]->err = "\0";
  init_sig_handler_2(sig);
}
