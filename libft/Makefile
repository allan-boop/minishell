#########################################
## ARGUMENTS
#########################################

INCLUDES_PATH = ../include
NAME		= libft.a
CFLAGS		= -Wextra -Wall -Werror -I$(INCLUDES_PATH)
CC			= gcc

########################################
## SOURCES
########################################

SRC_FILES = ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_atoi_base.c \
				ft_atol.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_printf.c \
				ft_write_args_c.c \
				ft_write_args_d.c \
				ft_write_args_u.c \
				ft_write_args_percent.c \
				ft_write_args_x.c \
				ft_write_args_p.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_count_words.c \
				ft_len_y.c \
				ft_len_x.c \
				ft_strlower.c \
				ft_strcmp.c

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
