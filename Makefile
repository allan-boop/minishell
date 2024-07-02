#########################################
## ARGUMENTS
#########################################
NAME	= minishell

INCLUDES_PATH=	include
CC=				gcc
CFLAGS=			-Wall -Wextra -Werror -g3

LIBS_DIR=	./libft

all: $(NAME)

########################################
## SOURCES
########################################
SRC_FILES =	minishell.c \
			set_env.c \
			ft_loop.c \
			ft_error.c \
			ft_signal.c \
			exec/utils.c \
			exec/utils.c \
			get_next_line.c \
			get_next_line_utils.c \
			exec/shlvl.c \
			ft_error_two.c \
			pars/parsing.c \
			exec/close_fd.c \
			ft_init_shell.c \
			pars/env_shell.c \
			malloc_factory.c \
			builtins/ft_cd.c \
			exec/exe_utils.c \
			exec/execution.c \
			builtins/ft_env.c \
			pars/give_token.c \
			builtins/ft_pwd.c \
			pars/utils_envp.c \
			exec/gnl.c \
			exec/utils_redirection.c \
			pars/utils_parsing_exp_two.c \
			exec/ft_other_b_in.c \
			exec/utils_fork.c \
			exec/ft_parent_p.c \
			pars/ft_find_var.c \
			builtins/ft_exit.c \
			builtins/ft_echo.c \
			pars/create_list.c \
			ft_free_copy_envp.c \
			pars/utils_export.c \
			pars/ft_del_quote.c \
			pars/ft_copy_envp.c \
			m_factory_manager.c \
			builtins/ft_unset.c \
			pars/utils_parsing.c \
			builtins/ft_export.c \
			pars/ft_space_pipe.c \
			pars/ft_split_shell.c \
			exec/ft_redirection.c \
			exec/other_builtins.c \
			exec/ft_close_pipefd.c \
			pars/ft_replace_doll.c \
			pars/ft_calloc_shell.c \
			builtins/ft_cd_utils.c \
			builtins/ft_cd_setenv.c \
			pars/ft_space_chevron.c \
			builtins/ft_cd_utils2.c \
			builtins/ft_echo_utils.c \
			pars/utils_parsing_exp.c \
			pars/utils_parsing_cmd.c \
			builtins/ft_env_own_arg.c \
			builtins/ft_no_unset_env.c \
			builtins/ft_export_utils.c \
			builtins/ft_export_modify.c \
			builtins/ft_export_add_var.c \
			pars/utils_export_quote.c

SRC_FILES := $(addprefix src/, $(SRC_FILES))
OBJ_FILES = $(SRC_FILES:.c=.o)

########################################
## RULES
########################################

all: $(NAME)

DO_LIBS:
	@echo DOING LIBS
	@make -C $(LIBS_DIR) all

$(NAME): $(OBJ_FILES) | DO_LIBS
	@echo LINKING
	@$(CC) $^ -L$(LIBS_DIR) -lft -lreadline $(CFLAGS) -o $@ -lm

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)
	@make -C $(LIBS_DIR) clean

fclean: clean
	@make -C $(LIBS_DIR) fclean
	@rm -f $(NAME)

val :
	@valgrind -s --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all --trace-children=yes --gen-suppressions=all --suppressions=/home/gdoumer/Documents/minishell/valgrind.supp --quiet ./minishell

re: fclean all

.PHONY: all clean fclean re all
