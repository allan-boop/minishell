#include "../include/minishell.h"


void	proc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, proc_signal_handler);
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		signal(SIGINT, signal_handler);
	}
	else if (sig == SIGQUIT)
		signal(SIGQUIT, signal_handler);
}
