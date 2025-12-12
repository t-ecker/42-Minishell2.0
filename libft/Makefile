NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = \
	./src/mandetory/ft_atoi.c \
	./src/mandetory/ft_bzero.c \
	./src/mandetory/ft_calloc.c \
	./src/mandetory/ft_isalnum.c \
	./src/mandetory/ft_isalpha.c \
	./src/mandetory/ft_isascii.c \
	./src/mandetory/ft_isdigit.c \
	./src/mandetory/ft_isprint.c \
	./src/mandetory/ft_isspace.c \
	./src/mandetory/ft_itoa.c \
	./src/mandetory/ft_memchr.c \
	./src/mandetory/ft_memcmp.c \
	./src/mandetory/ft_memcpy.c \
	./src/mandetory/ft_memmove.c \
	./src/mandetory/ft_memset.c \
	./src/mandetory/ft_putchar_fd.c \
	./src/mandetory/ft_putendl_fd.c \
	./src/mandetory/ft_putnbr_fd.c \
	./src/mandetory/ft_putstr_fd.c \
	./src/mandetory/ft_split.c \
	./src/mandetory/ft_strchr.c \
	./src/mandetory/ft_strdup.c \
	./src/mandetory/ft_striteri.c \
	./src/mandetory/ft_strjoin.c \
	./src/mandetory/ft_strlcat.c \
	./src/mandetory/ft_strlcpy.c \
	./src/mandetory/ft_strlen.c \
	./src/mandetory/ft_strmapi.c \
	./src/mandetory/ft_strncmp.c \
	./src/mandetory/ft_strnstr.c \
	./src/mandetory/ft_strrchr.c \
	./src/mandetory/ft_strtrim.c \
	./src/mandetory/ft_substr.c \
	./src/mandetory/ft_tolower.c \
	./src/mandetory/ft_toupper.c

SRC_BONUS = \
	./src/bonus/ft_lstnew_bonus.c \
	./src/bonus/ft_lstadd_front_bonus.c \
	./src/bonus/ft_lstsize_bonus.c \
	./src/bonus/ft_lstlast_bonus.c \
	./src/bonus/ft_lstadd_back_bonus.c \
	./src/bonus/ft_lstdelone_bonus.c \
	./src/bonus/ft_lstiter_bonus.c \
	./src/bonus/ft_lstclear_bonus.c \
	./src/bonus/ft_lstmap_bonus.c

SRC_EXTRA = ./src/get_next_line/get_next_line.c \
			./src/printf/ft_printf.c \
			./src/printf/print_c.c \
			./src/printf/print_x_X.c \
			./src/printf/print_u.c \
			./src/printf/print_s.c \
			./src/printf/print_p.c \
			./src/printf/print_i_d.c \

OBJ_DIR = ./obj
OBJ_FILES		=	$(patsubst ./src/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_FILES_BONUS	=	$(patsubst ./src/%.c, $(OBJ_DIR)/%.o, $(SRC_BONUS))
OBJ_FILES_EXTRA	=	$(patsubst ./src/%.c, $(OBJ_DIR)/%.o, $(SRC_EXTRA))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $^

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ_FILES) $(OBJ_FILES_BONUS)
	@ar rcs $(NAME) $^

extra: $(OBJ_FILES) $(OBJ_FILES_BONUS) $(OBJ_FILES_EXTRA)
	@ar rcs $(NAME) $^

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus extra