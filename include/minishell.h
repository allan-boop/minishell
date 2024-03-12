#ifndef MINISHELL_H
# define MINISHELL_H

# define MANY_ARGS "Too many arguments.\n"
# define MALLOC_FAIL "Error: malloc failed.\n"

# include "libft.h"
# include <term.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <curses.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_malloc_ptr
{
	void			*ptr;
	t_malloc_ptr	*next;
}	t_malloc_ptr;

typedef struct s_tree
{
	char	*content;
	bool	is_sign;
	bool	is_command;
	char	*path;
	bool	is_other;
	t_tree	*child;
	t_tree	parent;
}	t_tree;

typedef struct s_mini
{
	char	**tab_pars;
	t_tree	*ast;
}	t_mini;


void	ft_loop(char **envp);
void	ft_nb_args(int argc);
void	init_struct(t_mini **shell);
void	ft_parsing(t_mini *shell, char *line);
void	ft_execution(t_mini *shell, char **envp);
void	create_ast(t_mini *shell);

#endif
