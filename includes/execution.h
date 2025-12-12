/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:10:16 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:10:17 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_shell	t_shell;

typedef struct s_piper
{
	int	pipe_fd[2];
	int	prev_fd;
	int	last_pid;
}	t_piper;

typedef enum s_builtin_type
{
	NONE,
	EXIT,
	PWD,
	CD,
	ENV,
	EXPORT,
	UNSET,
	ECHOO
}	t_builtin_type;

typedef enum e_heredoc_status
{
	HEREDOC_SUCCESS,
	HEREDOC_FAILED,
	HEREDOC_SIGNAL
}	t_heredoc_status;

bool	execute_heredoc(t_shell *shell, t_ast_node *node);
int		execute(t_shell *shell, t_ast_node *node);
int		execute_cmd(t_shell *shell, t_ast_node *node, bool exec_in_child);
int		execute_logical(t_shell *shell, t_ast_node *node);
int		execute_pipe(t_shell *shell, t_ast_node *node);
int		get_exit_code(int status);

int		handle_redirections(t_shell *shell, t_redirectList *node);
void	update_underscore(t_shell *shell, char **args, char *path);
int		get_exit_code(int status);
char	**args_to_array(t_shell *shell, t_ast_node *node);
int		get_cmd_path(char *cmd, t_shell *shell, char **path);

char	*generate_heredoc_filename(t_shell *shell);
void	handle_readline_error(int stdin_backup, char *target);

int		ft_env(char **args, t_shell *shell);
int		ft_export(char **args, t_shell *shell);
int		ft_unset(char **args, t_shell *shell);
int		ft_echo(char **args);
int		ft_pwd(t_shell *shell);
int		ft_cd(char **args, t_shell *shell);
int		ft_exit(char **args, t_shell *shell);

#endif