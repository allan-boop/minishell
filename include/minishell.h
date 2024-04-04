#ifndef MINISHELL_H
# define MINISHELL_H

# define MANY_ARGS "Too many arguments.\n"
# define MALLOC_FAIL "Error: malloc failed.\n"
# define SIGNAL_FAIL "Error: signal failed.\n"
# define REDIR_FAIL "Error syntax: redirection failed.\n"
# define OPERATOR_FAIL "Error syntax: operator failed.\n"
# define QUOTE_FAIL "Error syntax: quote failed.\n"
# define PIPE_FAIL "Error syntax: pipe failed.\n"
# define NEW 2
# define DELETE 3
# define CLEAR 4
# define PROMPT "pikapika$ "

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
# include <malloc.h>
# include <stdbool.h>
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
	void				*ptr;
	struct s_malloc_ptr	*next;
}	t_malloc_ptr;

typedef struct s_list_struct
{
	char					*content;
	bool					is_operator;
	bool					is_redir;
	bool					error_parsing;
	struct s_list_struct	*next;
	struct s_list_struct	*prev;
}	t_list_struct;

typedef struct s_envp
{
	char			*var;
	char			*tmp_var;
	int				index;
	int				last_return;
	struct t_envp	*next;
}	t_envp;

typedef struct s_mini
{
	char			**tab_pars;
	t_list_struct	*list;
	t_envp			*team_envp;
}	t_mini;

void			ft_signal(void);
void			*ft_del_all(void);
bool			ft_pwd(void);
bool			ft_exit(void);
bool			ft_echo(t_mini *shell);
void			*ft_alloc(int size);
void			ft_nb_args(int argc);
void			ft_loop(char **envp);
bool			ft_error(char *cmd, char *msg, int ret);
void			ft_replace_space_in_str(char *line);
int				syntax_error(char *msg);
void			*ft_del_alloc(void *var);
char			*ft_space_pipe(char *line);
int				ft_check_quote(char *line);
t_list_struct	*create_list(t_mini *shell);
char			**ft_copy_envp(char **envp, t_mini *shell);
int				ft_len_space_pipe(char *line);
void			ft_replace_space(char **line);
void			give_token(t_list_struct *node);
char			*ft_strdup_shell(const char *s);
bool			ft_cd(t_mini *shell, char **envp);
int				ft_parsing(t_mini *shell, char *line);
int				ft_error_parsing(t_list_struct	*list);
char			**ft_put_space_between(char **tab_line);
char			**ft_split_shell(char const *s, char c);
char			*find_path(char *tab_line, char **envp);
size_t			count_words_split(char const *s, char c);
void			ft_execution(t_mini *shell, char **envp);
t_list_struct	*create_node_list(t_mini *shell, size_t i);
char			*ft_strjoin_shell(char const *s1, char const *s2);
void			*malloc_factory(size_t size, int type, void *ptr);
void			*malloc_factory(size_t size, int type, void *ptr);
int				ft_len_space_redirect(int *i, char *line, size_t *len);
void			ft_space_redirect(int *i, int *j, char *line, char *tmp);
void			add_node_front(t_list_struct *list, t_list_struct *node);
void			del_node_list(t_list_struct **list, t_list_struct *node);
void			del_if_same(t_malloc_ptr *l_m, t_malloc_ptr *tmp, void *var);
char			*ft_substr_shell(char const *s, unsigned int start, size_t len);

#endif
