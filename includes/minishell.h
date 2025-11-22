#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char *input;
	int exit_code;
	char *env;	// env can be other type idk

} t_shell;

# include "../libft/libft.h"
# include "errors.h"

void free_shell(t_shell *shell);



void exit_code(t_shell *shell, int code);



int input_validation(t_shell *shell);
int check_quotes(char *str);
int check_redir(char *str);
int check_parentheses(char *str);
int check_pipes(char *str);
int check_and_operator(char *str);

int get_input(t_shell *shell);
bool is_special_char(char c);
void skip_quotes(char *str, int *pos);
void skip_spaces(char *str, int *pos);
void toggleBool(bool *input);
void toggle_quote(char c, bool *openDoubleQuote, bool *openSingleQuote);

// void free_env(idk)

# endif