/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:11:09 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:11:10 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		delete_env_var(args[i], shell);
		++i;
	}
	return (0);
}
