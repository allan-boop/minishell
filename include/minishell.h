/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:29:59 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:30:07 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define INVALID_OPTION "Invalid option.\n"
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
# include <fcntl.h>
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

extern volatile int	g_sig;

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

typedef struct s_envp_struct
{
	char	**copy_envp;
	bool	pwd;
	bool	oldpwd;
	bool	home;
	bool	shlvl;
	bool	path;
}	t_env;

typedef struct s_mini
{
	int				og_stdin;
	int				og_stdout;
	char			**tab_pars;
	char			**tab_cmd;
	int				status;
	bool			pipe;
	int				i_p;
	int				**pipe_fd;
	int				tab_index;
	int				i;
	int				filein;
	int				fileout;
	t_list_struct	*list;
	t_envp			*team_envp;
}	t_mini;

typedef struct s_str_utils
{
	size_t	start;
	size_t	end;
}	t_str_utils;

typedef struct s_int_utils
{
	int		i;
	int		j;
	char	**envp;
	t_env	*env;
}	t_int_utils;

char			*ft_strjoin_char(char *s1, char c);
char			*ft_cat_str(t_mini *shell, t_int_utils *utils,
					char *n_str, int *i);
char			*skip_bef_doll( char *tab_pars, t_int_utils *utils,
					bool *quote, char *n_str);
char			*skip_doll_betw_q(char *tab_pars, char *n_str,
					t_int_utils *utils, bool *quote);
char			*skip_env_var(char *str, char *n_str,
					t_int_utils *utils, int *k);
void			ft_here_doc_while(t_mini *shell, int *i, t_env *env, int *fd);
void			ft_here_doc_in(t_env *env, int *fd, t_mini *shell);
int				gnl(char **line, int i, int r, char c);
void			proc_signal_handler_heredoc_parent(int sig);
void			proc_signal_handler_heredoc(int sig);
void			close_fd(int fd);
void			*ft_del_all(void);
void			*ft_alloc(int size);
void			ft_nb_args(int argc);
char			*ft_itoa_shell(int n);
void			signal_handler(int sig);
int				ft_tab_len(char **envp);
int				syntax_error(char *msg);
void			*ft_del_alloc(void *var);
int				ft_count_quote(char *str);
int				ft_del_quotes(char **arg);
void			ft_mini_doc(t_mini *shell);
char			*ft_space_pipe(char *line);
int				ft_check_quote(char *line);
char			**ft_sort_envp(t_env *env);
char			*ft_clean_quotes(char *str);
void			ft_list_cmd(t_mini **shell);
t_list_struct	*create_list(t_mini *shell);
void			proc_signal_handler(int sig);
void			ft_free_copy_envp(t_env *env);
int				ft_len_space_pipe(char *line);
void			ft_replace_space(char **line);
void			ft_close_pipefd(t_mini *shell);
t_envp			*ft_lstnew_envp(void *content);
void			give_token(t_list_struct *node);
char			*ft_strdup_shell(const char *s);
char			**ft_sort_envp_char(char **envp);
void			ft_loop(char **envp, t_env *env);
int				ft_count_arg_fork(t_mini *shell);
char			*ft_find_name_var(char *content);
bool			ft_cd(t_mini *shell, t_env *env);
int				ft_execve(char *str, t_env *env);
void			ft_error_malloc(char **tab_shell);
char			*ft_find_value_var(char *content);
int				ft_current_arg(char *current_arg);
bool			ft_pwd(t_mini *shell, t_env *env);
bool			ft_echo(t_mini *shell, t_env *env);
char			*ft_getenv(char *name, char **envp);
bool			ft_unset(t_mini *shell, t_env *env);
char			**ft_copy_envp_no_sort(char **envp);
void			ft_dell_all_quote_export(char *line);
int				ft_replace_quote_export(char **line);
void			proc_signal_handler_heredoc(int sig);
bool			other_builtin(char *cmd, t_env *env);
void			inc_shlvl(t_mini *shell, t_env *env);
bool			ft_export(t_mini *shell, t_env *env);
int				ft_is_in_quote(char *line, char *str);
bool			yes_unset_env(char *name, t_env *env);
int				ft_error_parsing(t_list_struct	*list);
bool			check_cd_err(t_mini *shell, char *path);
void			ft_redir(t_mini *shell, char *cmd_next);
bool			ft_error(char *cmd, char *msg, int ret);
void			ft_dell_simple_quote_export(char *line);
void			ft_dell_double_quote_export(char *line);
char			**ft_put_space_between(char **tab_line);
bool			no_unset_env(t_mini *shell, t_env *env);
char			**ft_split_shell(char const *s, char c);
bool			ft_error(char *cmd, char *msg, int ret);
void			ft_copy_envp(t_env *env, t_mini *shell);
void			ft_init_shell(t_mini *shell, int status);
size_t			count_words_split(char const *s, char c);
void			ft_redirection(t_mini *shell, t_env *env);
char			*ft_replace_doll(char *line, char *value);
t_list_struct	*create_node_list(t_mini *shell, size_t i);
char			*find_path_execve_vol_two(char *tab_shell);
void			*ft_calloc_shell(size_t nmemb, size_t size);
char			*find_path_execve(char *tab_line, char **envp);
bool			ft_env(char **envp, t_env *env, t_mini *shell);
char			*if_exp_var(t_mini *shell, t_env *env, int *i);
bool			ft_print_export_alone(t_mini *shell, t_env *env);
bool			ft_exit(char **envp, t_env *env, t_mini **shell);
void			ft_setenv(char *name, char *value, char ***envp);
int				ft_check_last(char *current_arg, t_mini **shell);
void			ft_lstadd_back_envp(t_mini **shell, t_envp *new);
void			ft_close_pipefd_bis(t_mini *shell, int pipefd[2]);
void			ft_create_list(char ***copy_envp, t_mini **shell);
char			*ft_strjoin_shell(char const *s1, char const *s2);
int				ft_parsing(t_mini *shell, char *line, t_env *env);
void			*malloc_factory(size_t size, int type, void *ptr);
void			ft_execution(t_mini *shell, char **envp, t_env *env);
void			ft_replace_space_in_str(char *line, bool only_quote);
void			ft_parent_p(char *cmd_next, t_mini *shell, pid_t pid);
int				ft_len_space_redirect(int *i, char *line, size_t *len);
void			ft_setenv_shell(char *name, char *value, char ***envp);
void			ft_here_doc(t_mini *shell, int *i, int *fd, t_env *env);
void			set_env(char **envp, t_env *env, int argc, char **argv);
void			ft_space_redirect(int *i, int *j, char *line, char *tmp);
void			add_node_front(t_list_struct *list, t_list_struct *node);
void			del_node_list(t_list_struct **list, t_list_struct *node);
void			ft_change_path( t_mini *shell, t_env *env, char **oldcwd);
void			ft_find_dpointb(int *i, int *start, char **str, char **new);
void			del_if_same(t_malloc_ptr *l_m, t_malloc_ptr *tmp, void *var);
void			ft_add_new_var(t_mini **shell, t_env *env, char *existing_var);
void			ft_add_new_var(t_mini **shell, t_env *env, char *existing_var);
char			*ft_substr_shell(char const *s, unsigned int start, size_t len);
void			ft_check_plus(char **envp, char *just_name_var,
					char *existing_var);
bool			other_builtin_p(char *cmd, t_env *env,
					char *cmd_next, t_mini *shell);
void			ft_modify_var(t_mini *shell, char *existing_var,
					t_env *env, char *just_name_var);
#endif
