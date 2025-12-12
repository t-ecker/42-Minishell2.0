/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:13:05 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:13:06 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redir_syntax(char *str, int *pos)
{
	int		i;
	char	c;

	i = *pos;
	c = str[i];
	if (str[i + 1] == c)
		i++;
	i++;
	skip_spaces(str, &i);
	if (!str[i])
		return (syntax_error(SYNTAX_REDIR_EOF_ERROR), 1);
	if (str[i] == '&' && str[i + 1] == '&')
		return (syntax_error_unexpected_token_str("&&"), 1);
	if (str[i] == '|' && str[i + 1] == '|')
		return (syntax_error_unexpected_token_str("||"), 1);
	if (str[i] == '>' && str[i - 1] != '>' && str[i + 1])
		return (syntax_error_unexpected_token_str(">>"), 1);
	if (str[i] == '<' && str[i - 1] != '<' && str[i + 1])
		return (syntax_error_unexpected_token_str("<<"), 1);
	if (is_special_char(str[i]))
		return (syntax_error_unexpected_token(str[i]), 1);
	*pos = i - 1;
	return (0);
}

int	check_redir(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		skip_quotes(str, &pos);
		if (str[pos] == '>' || str[pos] == '<')
			if (handle_redir_syntax(str, &pos))
				return (1);
		if (str[pos])
			pos++;
	}
	return (0);
}
