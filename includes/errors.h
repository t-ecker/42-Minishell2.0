/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:10:11 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:10:12 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define FATAL_ERROR "minishell: fatal error: "
# define MALLOC_ERROR "malloc failed"
# define READLINE_ERROR "readline failed"
# define OPENDIR_ERROR "opendir failed"
# define DUP_ERROR "dup failed"
# define FORK_ERROR "fork failed"
# define PIPE_ERROR "pipe failed"

# define SYNTAX_ERROR "minishell: syntax error"
# define SYNTAX_PIPE_ERROR " near unexpected token `|'"
# define SYNTAX_QUOTE_ERROR "minishell: unexpected EOF while looking for \
matching `'/\"'\nminishell: syntax error: unexpected end of file"

# define MINISHELL_BASE "minishell: "
# define CMD_NOT_FOUND_ERROR "command not found"
# define NO_SUCH_FILE_ERROR "No such file or directory"
# define IS_DIR_ERROR "Is a directory"
# define PERMISSION_ERROR "Permission denied"

// # define SYNTAX_OUTPUT_ERROR " near unexpected token `<'"
// # define SYNTAX_INPUT_ERROR " near unexpected token `>'"
# define SYNTAX_PAREN_ERROR ": unexpected end of file"
# define SYNTAX_REDIR_EOF_ERROR " near unexpected token `newline'"

typedef struct s_shell	t_shell;

void	syntax_error(char *str);
void	syntax_error_unexpected_token(char c);
void	syntax_error_unexpected_token_str(char *c);
void	fatal_error(t_shell *shell, char *msg);
void	execution_error(char *str, char *cmd);
void	export_error(char c);
void	export_error_str(char *c);
void	exit_error_numeric(char *str);

#endif