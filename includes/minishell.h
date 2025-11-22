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
int input_validation(t_shell *shell);
int get_input(t_shell *shell);
void exit_code(t_shell *shell, int code);
// void free_env(idk)

# endif