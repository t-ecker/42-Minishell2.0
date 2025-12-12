/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:14:11 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:14:12 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	toggle_quote(char c, bool *openDoubleQuote, bool *openSingleQuote)
{
	if (c == '\'' && !*openDoubleQuote)
		toggle_bool(openSingleQuote);
	else if (c == '"' && !*openSingleQuote)
		toggle_bool(openDoubleQuote);
}

void	skip_quotes(char *str, int *pos)
{
	char	quote;

	if (str[*pos] == '\'' || str[*pos] == '"')
	{
		quote = str[(*pos)++];
		while (str[*pos] && str[*pos] != quote)
			(*pos)++;
		if (str[*pos] == quote)
			(*pos)++;
	}
}

char	*remove_quotes(char *str, t_shell *shell)
{
	int			pos;
	t_expand	e;
	char		quote;

	init_expander(&e, shell);
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '"')
		{
			quote = str[pos++];
			while (str[pos] && str[pos] != quote)
				append_char(str[pos++], &e);
			if (str[pos] == quote)
				++pos;
		}
		else
			append_char(str[pos++], &e);
	}
	return (e.res);
}

void	remove_quotes_from_list(t_argList *args, t_shell *shell)
{
	t_argList	*current;

	current = args;
	while (current)
	{
		current->value = remove_quotes(current->value, shell);
		current = current->next;
	}
}

bool	found_quote(char c, bool *inside_double_quote,
			bool *inside_single_quote, int *i)
{
	if (c == '\'' || c == '"')
	{
		toggle_quote(c, inside_double_quote, \
			inside_single_quote);
		++(*i);
		return (true);
	}
	return (false);
}
