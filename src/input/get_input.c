/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:12:41 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:12:42 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_input(t_shell *shell)
{
	shell->input = readline("minishell: ");
	if (!shell->input)
		return (1);
	gc_add(shell, shell->input);
	if (shell->input[0] != '\0')
		add_history(shell->input);
	return (0);
}
