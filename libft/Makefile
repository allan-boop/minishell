#########################################
## ARGUMENTS
#########################################

INCLUDES_PATH = ../includes
NAME		= libft.a
CFLAGS		= -Wextra -Wall -Werror -I$(INCLUDES_PATH)
CC			= gcc

########################################
## SOURCES
########################################

SRC_FILES =

OBJ_FILES =	$(SRC_FILES:.c=.o)

########################################
## RULES
########################################

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(AR) rcs $@ $(OBJ_FILES)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
