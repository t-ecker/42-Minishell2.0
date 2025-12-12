/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:12:59 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:13:00 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *str)
{
	int		pos;
	bool	open_single_quote;
	bool	open_double_quote;

	pos = 0;
	open_double_quote = false;
	open_single_quote = false;
	while (str[pos])
	{
		toggle_quote(str[pos], &open_double_quote, &open_single_quote);
		pos++;
	}
	if (open_double_quote || open_single_quote)
		return (syntax_error(SYNTAX_QUOTE_ERROR), 1);
	return (0);
}
