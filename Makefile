NAME = minishell
NAME_BONUS = minishell_bonus

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
CC = cc


SRC =		./src/main.c \
			./src/input/get_input.c \
			./src/input/input_validation.c \
			./src/input/validate_andOperator_pipes.c \
			./src/input/validate_parentheses.c \
			./src/input/validate_quotes.c \
			./src/input/validate_redirection.c \
			./src/utils/errors.c \
			./src/utils/free.c \
			./src/utils/utils.c \
			./src/lexer/lexer.c \
			./src/garbageCollector/garbageCollector.c \
			./src/parser/parser.c \
			./src/parser/parse_cmd.c \
			./src/parser/parse_logicalOP.c \
			./src/parser/parse_pipe.c \
			./src/parser/parse_redir.c \
			./src/parser/parse_group.c \
			./src/expander/expander.c \
			./src/expander/expand_variable.c \
			./src/expander/expand_wildcard.c \
			./src/env/env.c \
			./src/debug/token_debug.c \
			./src/debug/ast_debug.c \


# SRC_BONUS =	./src/

OBJ_DIR = ./obj
SRC_DIR = ./src

OBJ_FILES		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
# OBJ_FILES_BONUS	=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_BONUS))

all: $(NAME)
	clear;
	@$(MAKE) loading
	clear;

$(NAME): $(LIBFT) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIBFT) $(LDFLAGS) -o $@

$(LIBFT):	$(LIBFT_DIR)/.git
	@make extra -C $(LIBFT_DIR)

$(LIBFT_DIR)/.git:
	@echo "\033[33mInitializing Libft submodule...\033[0m"
	@git submodule update --init --recursive
	@echo "\033[32mLibft submodule initialized.\033[0m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# bonus:	$(NAME_BONUS)
# 	clear;
# 	@$(MAKE) loading
# 	clear;

# $(NAME_BONUS):	$(LIBFT) $(OBJ_FILES_BONUS) 
# 	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

loading:
	@for i in {1..42}; do \
		printf '%s' "█"; \
		sleep 0.01; \
	done

.PHONY: all clean fclean re loading bonus