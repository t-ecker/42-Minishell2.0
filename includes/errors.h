#ifndef ERRORS_H
# define ERRORS_H

# define FATAL_ERROR "minishell: fatal error: "
# define MALLOC_ERROR "malloc failed"
# define READLINE_ERROR "readline failed"


# define SYNTAX_ERROR "minishell: syntax error"
# define SYNTAX_PIPE_ERROR " near unexpected token `|'"
# define SYNTAX_QUOTE_ERROR "minishell: unexpected EOF while looking for \
matching `'/\"'\nminishell: syntax error: unexpected end of file"
// # define SYNTAX_OUTPUT_ERROR " near unexpected token `<'"
// # define SYNTAX_INPUT_ERROR " near unexpected token `>'"
# define SYNTAX_PAREN_ERROR ": unexpected end of file"
# define SYNTAX_REDIR_EOF_ERROR " near unexpected token `newline'"

#include "minishell.h"


void syntax_error(char *str);
void syntax_error_unexpected_token(char c);
void fatal_error(t_shell *shell, char *msg);

#endif