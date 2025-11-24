#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

typedef struct s_shell t_shell;

# include "errors.h"
# include "lexer.h"

typedef struct s_shell
{
	char *input;
	int exit_code;
	char *env;	// env can be other type idk
	t_tokenList *tokens;
} t_shell;



// input
int get_input(t_shell *shell);
int input_validation(t_shell *shell);
int check_quotes(char *str);
int check_redir(char *str);
int check_parentheses(char *str);
int check_pipes(char *str);
int check_and_operator(char *str);


// utils
bool is_special_char(char c);
void skip_quotes(char *str, int *pos);
void skip_spaces(char *str, int *pos);
void toggleBool(bool *input);
void toggle_quote(char c, bool *openDoubleQuote, bool *openSingleQuote);
void exit_code(t_shell *shell, int code);

void add_token(t_tokenList *list, TokenType type, char *value, t_shell *shell);
t_tokenList* create_tokenList(t_shell *shell);

void free_shell(t_shell *shell);
void free_tokens(t_tokenList *tokens);
// void free_env(idk)\


// lexer
void lexer(t_shell *shell);


// debug
void print_tokens(t_tokenList *tokens);



# endif