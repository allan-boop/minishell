#include "../include/minishell.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "^C", 2);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		signal(SIGINT, signal_handler);
	}
	else if (sig == SIGQUIT)
		signal(SIGQUIT, signal_handler);

}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
