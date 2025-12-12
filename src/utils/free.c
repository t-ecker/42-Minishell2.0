/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:14:03 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:14:04 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_shell *shell)
{
	t_env	*current;
	t_env	*next;

	current = shell->env_list;
	while (current)
	{
		free(current->key);
		free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_all(t_shell *shell)
{
	gc_free_all(shell);
	free_env(shell);
}

void	gc_free_all(t_shell *shell)
{
	t_gc_node	*current;
	t_gc_node	*next;

	if (!shell->gc.head)
		return ;
	current = shell->gc.head;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	shell->gc.head = NULL;
}
