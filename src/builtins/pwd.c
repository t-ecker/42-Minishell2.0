/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:11:04 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:11:05 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = gc_add(shell, getcwd(NULL, 0));
	ft_putendl_fd(pwd, 1);
	return (0);
}
