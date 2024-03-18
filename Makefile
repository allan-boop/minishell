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
			utils.c \
			ft_loop.c \
			parsing.c \
			ft_error.c \
			execution.c \
			ft_signal.c \
			create_ast.c \
			ft_split_shell.c \
			malloc_factory.c \
			ft_substr_shell.c \
			ft_strdup_shell.c \
			m_factory_manager.c

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
