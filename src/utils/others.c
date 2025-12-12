/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:14:07 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:14:08 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_code(t_shell *shell, int code)
{
	shell->exit_code = code;
}

bool	is_special_char(char c)
{
	return (c == '|' || c == '&' || c == '(' || c == ')'
		|| c == '<' || c == '>');
}

void	skip_spaces(char *str, int *pos)
{
	while (str[*pos] && ft_isspace(str[*pos]))
		(*pos)++;
}

void	toggle_bool(bool *input)
{
	*input = !(*input);
}
