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
			ft_loop.c \
			ft_error.c \
			ft_signal.c \
			pars/ft_path.c \
			pars/parsing.c \
			malloc_factory.c \
			builtins/ft_cd.c \
			exec/execution.c \
			pars/give_token.c \
			builtins/ft_pwd.c \
			pars/utils_envp.c \
			pars/ft_find_var.c \
			builtins/ft_exit.c \
			builtins/ft_echo.c \
			pars/create_list.c \
			pars/utils_export.c \
			pars/ft_copy_envp.c \
			m_factory_manager.c \
			pars/utils_parsing.c \
			builtins/ft_export.c \
			pars/ft_space_pipe.c \
			pars/ft_split_shell.c \
			pars/ft_space_chevron.c \
			exec/utils.c

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

re: fclean all

.PHONY: all clean fclean re all
