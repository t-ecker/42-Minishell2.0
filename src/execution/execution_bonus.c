/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:11:48 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:11:49 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_backup_fds(t_shell *shell, int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdin_backup == -1 || *stdout_backup == -1)
	{
		if (*stdin_backup != -1)
			close(*stdin_backup);
		if (*stdout_backup != -1)
			close(*stdout_backup);
		fatal_error(shell, DUP_ERROR);
	}
}

void	restore_fds(t_shell *shell, int stdin_backup, int stdout_backup)
{
	if (dup2(stdin_backup, STDIN_FILENO) == -1
		|| dup2(stdout_backup, STDOUT_FILENO) == -1)
	{
		close(stdin_backup);
		close(stdout_backup);
		fatal_error(shell, DUP_ERROR);
	}
	close(stdin_backup);
	close(stdout_backup);
}

int	execute(t_shell *shell, t_ast_node *node)
{
	int	stdin_backup;
	int	stdout_backup;
	int	res;

	get_backup_fds(shell, &stdin_backup, &stdout_backup);
	res = 0;
	if (node->type == AST_COMMAND)
		res = execute_cmd(shell, node, true);
	else if (node->type == AST_PIPE)
		res = execute_pipe(shell, node);
	else if (node->type == AST_LOGICAL_OP)
		res = execute_logical(shell, node);
	else if (node->type == AST_GROUP)
		res = execute(shell, node->u_data.group.child);
	restore_fds(shell, stdin_backup, stdout_backup);
	shell->exit_code = res;
	return (res);
}
