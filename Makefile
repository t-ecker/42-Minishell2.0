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
			./src/utils/execution_errors.c \
			./src/utils/free.c \
			./src/utils/others.c \
			./src/utils/quote_handling.c \
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
			./src/expander/word_split.c \
			./src/expander/expand_wildcard.c \
			./src/expander/wildcard_utils.c \
			./src/env/create_env_list.c \
			./src/env/utils.c \
			./src/signals/signals.c \
			./src/signals/utils.c \
			./src/execution/execution.c \
			./src/execution/execute_cmd.c \
			./src/execution/execute_cmd_path.c \
			./src/execution/execute_cmd_utils.c \
			./src/execution/execute_redirection.c \
			./src/execution/execute_pipe.c \
			./src/execution/execute_logical.c \
			./src/execution/heredoc.c \
			./src/execution/heredoc_utils.c \
			./src/builtins/env.c \
			./src/builtins/export.c \
			./src/builtins/unset.c \
			./src/builtins/echo.c \
			./src/builtins/pwd.c \
			./src/builtins/cd.c \
			./src/builtins/exit.c \


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