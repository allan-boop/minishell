#include "../include/minishell.h"

void	enable_echo_quit(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	t.c_cc[VQUIT] = 28;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	disable_echo_quit(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	t.c_cc[VQUIT] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	empty_signal_handler(int sig)
{
	(void)sig;
}

void	proc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, proc_signal_handler);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit\n", 5);
		signal(SIGQUIT, proc_signal_handler);
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
	{
		disable_echo_quit();
		signal(SIGQUIT, empty_signal_handler);
	}
}
