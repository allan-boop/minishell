#include "../include/minishell.h"

void	proc_signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_sig = sig;
	}
	if (sig == SIGQUIT)
	{
		write(1, "\b\b\b\b    \b\b\b\b", 12);
	}
}

void	proc_signal_handler_heredoc_parent(int sig)
{
	(void)sig;
	return ;
}

void	proc_signal_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
		write(1, "Quit\n", 5);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
	}
}
