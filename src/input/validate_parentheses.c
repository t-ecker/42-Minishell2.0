/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parentheses.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:12:55 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:12:56 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_parenthese_syntax(char *str, int *pos)
{
	(*pos)++;
	skip_spaces(str, pos);
	if (str[*pos] == '|' || str[*pos] == '&' || str[*pos] == ')')
		return (syntax_error_unexpected_token(str[*pos]), 1);
	return (0);
}

int	check_parentheses(char *str)
{
	int	pos;
	int	count;

	pos = 0;
	count = 0;
	while (str[pos])
	{
		skip_quotes(str, &pos);
		if (str[pos] == '(')
		{
			count++;
			if (handle_parenthese_syntax(str, &pos))
				return (1);
			continue ;
		}
		else if (str[pos] == ')')
			if (--count < 0)
				return (syntax_error_unexpected_token(')'), 1);
		if (str[pos])
			pos++;
	}
	if (count != 0)
		return (syntax_error(SYNTAX_PAREN_ERROR), 1);
	return (0);
}
