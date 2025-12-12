/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:14:18 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:14:19 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_args(int argc)
{
	if (argc != 1)
	{
		ft_putendl_fd("Invalid input", 2);
		exit(1);
	}
}

void	reset(t_shell *shell)
{
	setup_main_signals();
	shell->input = NULL;
	shell->wildcard_expansion_counter = 0;
	shell->heredoc_counter = 0;
}

// all allocations inside the loop are stored inside a garbageCollector so
	// that its easier to free (especially on errors)
// but all persistant data like env must be freed normally

void	loop(t_shell *shell)
{
	while (1)
	{
		reset(shell);
		if (get_input(shell))
			break ;
		if (input_validation(shell))
		{
			gc_free_all(shell);
			shell->exit_code = 2;
			continue ;
		}
		lexer(shell);
		parser(shell);
		if (!execute_heredoc(shell, shell->ast))
		{
			gc_free_all(shell);
			continue ;
		}
		execute(shell, shell->ast);
		gc_free_all(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	ft_memset(&shell, 0, sizeof(t_shell));
	check_args(argc);
	create_env_list(&shell, envp);
	loop(&shell);
	free_env(&shell);
	return (0);
}
