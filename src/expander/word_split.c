/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:12:30 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:12:31 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_word(char *str, int *pos, t_shell *shell)
{
	t_expand	word;

	init_expander(&word, shell);
	while (str[*pos])
	{
		if (str[*pos] == '\'' || str[*pos] == '"')
		{
			toggle_quote(str[*pos], &word.inside_double_quote, \
				&word.inside_single_quote);
			append_char(str[(*pos)++], &word);
			continue ;
		}
		if ((ft_isspace(str[*pos]) || str[*pos] == '\n')
			&& !word.inside_single_quote && !word.inside_double_quote)
			break ;
		append_char(str[*pos], &word);
		(*pos)++;
	}
	return (word.res);
}

t_argList	*word_split(char *str, t_shell *shell)
{
	t_argList	*head;
	char		*word;
	int			pos;

	if (!str)
		return (NULL);
	pos = 0;
	head = NULL;
	while (str[pos])
	{
		skip_spaces(str, &pos);
		if (!str[pos])
			break ;
		word = build_word(str, &pos, shell);
		if (word && word[0])
			add_arg_node(&head, word, shell);
	}
	return (head);
}
