/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:11:56 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:11:57 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_readline_error(int stdin_backup, char *target)
{
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	if (g_signal_received != SIGINT)
	{
		ft_putstr_fd("minishell: warning: here-document ", \
			STDERR_FILENO);
		ft_putstr_fd("delimited by end-of-file (wanted `", \
				STDERR_FILENO);
		ft_putstr_fd(target, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
	}
	setup_main_signals();
}

char	*generate_heredoc_filename(t_shell *shell)
{
	char	*res;

	res = gc_add(shell, ft_itoa(shell->heredoc_counter++));
	res = gc_add(shell, ft_strjoin("/tmp/.heredoc_", res));
	return (res);
}
