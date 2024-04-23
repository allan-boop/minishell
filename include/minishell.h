#ifndef MINISHELL_H
# define MINISHELL_H

# define MANY_ARGS "Too many arguments.\n"
# define NOT_ENOUGH_ARG "Not enough argument.\n"
# define MALLOC_FAIL "Error: malloc failed.\n"
# define SIGNAL_FAIL "Error: signal failed.\n"
# define REDIR_FAIL "Error syntax: redirection failed.\n"
# define OPERATOR_FAIL "Error syntax: operator failed.\n"
# define QUOTE_FAIL "Error syntax: quote failed.\n"
# define PIPE_FAIL "Error syntax: pipe failed.\n"
# define INVALID_IDENTIFIER "Is not a valid identifier.\n"
# define ERROR_EXECVE "Error execve.\n"
# define ERROR_PATH "Error path.\n"
# define ERROR_FORK "Error fork.\n"
# define ERROR_PIPE "Error pipe.\n"
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
	char			*whole_var;
	char			*var;
	char			*value;
	int				last_return;
	struct s_envp	*next;
}	t_envp;

typedef struct s_mini
{
	char			**tab_pars;
	char			**tab_cmd;
	int				tab_index;
	t_list_struct	*list;
	t_envp			*team_envp;
}	t_mini;

typedef struct s_str_utils
{
	size_t	start;
	size_t	end;
}	t_str_utils;

bool			ft_exit(void);
void			ft_signal(void);
void			*ft_del_all(void);
void			*ft_alloc(int size);
bool			ft_pwd(char **envp);
void			ft_nb_args(int argc);
void			ft_loop(char **envp);
int				ft_tab_len(char **envp);
int				syntax_error(char *msg);
void			*ft_del_alloc(void *var);
int				ft_del_quotes(char **arg);
void			ft_list_cmd(t_mini **shell);
char			*ft_space_pipe(char *line);
int				ft_check_quote(char *line);
char			**ft_sort_envp(char **envp);
t_list_struct	*create_list(t_mini *shell);
int				ft_len_space_pipe(char *line);
void			ft_replace_space(char **line);
t_envp			*ft_lstnew_envp(void *content);
void			give_token(t_list_struct *node);
char			*ft_strdup_shell(const char *s);
void			f_find_dpointb(int *i, int *start, char **str, char **new);
int				ft_count_arg_fork(t_mini *shell);
int				ft_check_last(char *current_arg);
char			*ft_find_name_var(char *content);
bool			ft_cd(t_mini *shell, char **envp);
void			ft_error_malloc(char **tab_shell);
char			*ft_find_value_var(char *content);
int				ft_execve(char *str, char **envp);
char			**ft_copy_envp_no_sort(char **envp);
bool			ft_echo(t_mini *shell, char **envp);
char			*ft_getenv(char *name, char **envp);
bool			ft_unset(t_mini *shell, char **envp);
int				ft_replace_quote_export(char **line);
bool			ft_print_export_alone(t_mini *shell);
void			ft_dell_all_quote_export(char *line);
bool			ft_env(char **envp, char **copy_envp);
int				ft_is_in_quote(char *line, char *str);
bool			ft_export(t_mini *shell, char **envp);
int				ft_parsing(t_mini *shell, char *line);
int				ft_error_parsing(t_list_struct	*list);
bool			ft_error(char *cmd, char *msg, int ret);
void			ft_dell_simple_quote_export(char *line);
void			ft_dell_double_quote_export(char *line);
char			**ft_put_space_between(char **tab_line);
char			**ft_split_shell(char const *s, char c);
bool			ft_error(char *cmd, char *msg, int ret);
char			*find_path(char *tab_shell, char **envp);
size_t			count_words_split(char const *s, char c);
void			ft_copy_envp(char **envp, t_mini *shell);
bool			other_builtin(char *cmd, char **envp);
t_list_struct	*create_node_list(t_mini *shell, size_t i);
void			ft_create_list(char **envp, t_mini **shell);
void			ft_change_path( t_mini *shell, char **envp, char **oldcwd);
int				ft_current_arg(char *current_arg, char **envp);
char			*find_path_execve(char *tab_line, char **envp);
void			ft_lstadd_back_envp(t_mini **shell, t_envp *new);
char			*ft_strjoin_shell(char const *s1, char const *s2);
void			*malloc_factory(size_t size, int type, void *ptr);
void			ft_replace_space_in_str(char *line, bool only_quote);
int				ft_len_space_redirect(int *i, char *line, size_t *len);
void			ft_space_redirect(int *i, int *j, char *line, char *tmp);
void			add_node_front(t_list_struct *list, t_list_struct *node);
void			del_node_list(t_list_struct **list, t_list_struct *node);
void			ft_execution(t_mini *shell, char **envp, char **copy_envp);
void			del_if_same(t_malloc_ptr *l_m, t_malloc_ptr *tmp, void *var);
void			ft_modify_var(t_mini *shell, char *existing_var, char **envp);
char			*ft_substr_shell(char const *s, unsigned int start, size_t len);
void			ft_add_new_var(t_mini **shell, char **envp, char *existing_var);
void			ft_check_plus(char **envp, char *just_name_var, char *existing_var);
#endif
