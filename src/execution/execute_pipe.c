/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:11:39 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:11:40 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_pipe_child(t_shell *shell, t_ast_node *cmd, t_piper p, \
		t_pipelineList *next)
{
	setup_child_signals();
	if (p.prev_fd != -1)
	{
		if (dup2(p.prev_fd, STDIN_FILENO) == -1)
			fatal_error(shell, DUP_ERROR);
		close(p.prev_fd);
	}
	if (next)
	{
		close(p.pipe_fd[0]);
		if (dup2(p.pipe_fd[1], STDOUT_FILENO) == -1)
			fatal_error(shell, DUP_ERROR);
		close(p.pipe_fd[1]);
	}
	exit(execute_cmd(shell, cmd, false));
}

int	wait_for_children(t_piper p)
{
	int	status;
	int	exit_code;

	waitpid(p.last_pid, &status, 0);
	exit_code = get_exit_code(status);
	while (wait(NULL) > 0)
		;
	return (exit_code);
}

void	execute_pipe_parent(t_piper *p, int pid, t_pipelineList *next)
{
	if (p->prev_fd != -1)
		close(p->prev_fd);
	if (next)
	{
		close(p->pipe_fd[1]);
		p->prev_fd = p->pipe_fd[0];
	}
	else
		p->last_pid = pid;
}

int	execute_pipe(t_shell *shell, t_ast_node *node)
{
	t_piper			p;
	t_pipelineList	*current;
	t_pipelineList	*next;
	int				pid;

	current = node->u_data.pipeline.commands;
	p.prev_fd = -1;
	p.last_pid = -1;
	while (current)
	{
		next = current->next;
		if (next)
			if (pipe(p.pipe_fd) == -1)
				fatal_error(shell, PIPE_ERROR);
		pid = fork();
		if (pid < 0)
			fatal_error(shell, FORK_ERROR);
		if (pid == 0)
			execute_pipe_child(shell, current->command, p, next);
		execute_pipe_parent(&p, pid, next);
		current = next;
	}
	return (wait_for_children(p));
}
