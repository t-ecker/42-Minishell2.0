/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:11:43 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:11:45 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_and_redirect(char *target, int fd_target, int flags, mode_t mode)
{
	int	fd;

	fd = open(target, flags, mode);
	if (fd == -1)
		return (-1);
	if (dup2(fd, fd_target) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	execute_redir_type(t_redirectList *node, char *target)
{
	int	result;

	result = -1;
	if (node->type == REDIR_INPUT)
		result = open_and_redirect(target, STDIN_FILENO, O_RDONLY, 0);
	else if (node->type == REDIR_OUTPUT)
		result = open_and_redirect(target, STDOUT_FILENO,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == REDIR_APPEND)
		result = open_and_redirect(target, STDOUT_FILENO,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->type == REDIR_HEREDOC)
	{
		result = open_and_redirect(target, STDIN_FILENO, O_RDONLY, 0);
		if (result == 0)
			unlink(target);
	}
	return (result);
}

int	execute_redirection(t_shell *shell, t_redirectList *node)
{
	t_argList	*expanded;
	int			result;

	expanded = expander(node->target, shell);
	if (!expanded || !expanded->value || !expanded->value[0] || expanded->next)
		return (execution_error("ambiguous redirect", node->target), 1);
	result = execute_redir_type(node, expanded->value);
	if (result == -1)
		return (execution_error(strerror(errno), expanded->value), 1);
	return (0);
}

int	handle_redirections(t_shell *shell, t_redirectList *node)
{
	t_redirectList	*current;

	current = node;
	while (current)
	{
		if (execute_redirection(shell, current))
			return (1);
		current = current->next;
	}
	return (0);
}
