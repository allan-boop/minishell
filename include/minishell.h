#ifndef MINISHELL_H
# define MINISHELL_H

# define MANY_ARGS "Too many arguments.\n"
# define MALLOC_FAIL "Error: malloc failed.\n"

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>


typedef struct s_mini
{
	int		i;
}	t_mini;


void	ft_loop(char **envp);
void	ft_nb_args(int argc);
void	init_struct(t_mini **shell);
void	ft_parsing(t_mini *shell, char *line);
void	ft_execution(t_mini *shell, char **envp);
void	ft_free_all(t_mini *shell, char *line);
void	create_ast(t_mini *shell);

#endif
