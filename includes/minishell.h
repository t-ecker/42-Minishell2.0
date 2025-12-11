#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h> 
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "../libft/libft.h"
# include "env.h"
# include "errors.h"
# include "lexer.h"
# include "parser.h"
# include "garbageCollector.h"
# include "expander.h"
# include "execution.h"

extern volatile sig_atomic_t	g_signal_received;

typedef struct s_shell
{
	t_gc		gc;
	char		*input;
	int			exit_code;
	int			heredoc_counter;
	int			wildcard_expansion_counter;
	t_env		*env_list;
	t_tokenList	tokens;
	t_ast_node	*ast;
}	t_shell;

// input
int		get_input(t_shell *shell);
int		input_validation(t_shell *shell);
int		check_quotes(char *str);
int		check_redir(char *str);
int		check_parentheses(char *str);
int		check_pipes(char *str);
int		check_and_operator(char *str);

// utils
bool	is_special_char(char c);
void	skip_quotes(char *str, int *pos);
void	skip_spaces(char *str, int *pos);
void	toggle_quote(char c, bool *openDoubleQuote, bool *openSingleQuote);
void	exit_code(t_shell *shell, int code);
char	*remove_quotes(char *str, t_shell *shell);
void	toggle_bool(bool *input);


void	free_all(t_shell *shell);
void	free_env(t_shell *shell);

void	setup_main_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);
void	enable_ctrl_c_echo(void);
void	disable_ctrl_c_echo(void);

// lexer
void	lexer(t_shell *shell);

// parser
void	parser(t_shell *shell);

#endif