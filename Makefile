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
			ft_path.c \
			parsing.c \
			ft_error.c \
			execution.c \
			ft_signal.c \
			utils_envp.c \
			give_token.c \
			create_list.c \
			ft_copy_envp.c \
			utils_parsing.c \
			ft_space_pipe.c \
			malloc_factory.c \
			builtins/ft_cd.c \
			ft_split_shell.c \
			builtins/ft_pwd.c \
			builtins/ft_exit.c \
			builtins/ft_echo.c \
			ft_space_chevron.c \
			m_factory_manager.c \
			builtins/ft_export.c
			utils.c

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
