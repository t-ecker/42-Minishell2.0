#include "../../includes/minishell.h"

int	handle_pipe_syntax(char *str, int *pos)
{
	int	skip;

	skip = 1;
	if (str[*pos + 1] && str[*pos + 1] == '|')
		skip = 2;
	*pos += skip;
	skip_spaces(str, pos);
	if (str[*pos] == '|' || str[*pos] == '&' || str[*pos] == ')')
		return (syntax_error_unexpected_token(str[*pos]), 1);
	return (0);
}

int	check_pipes(char *str)
{
	int	pos;

	pos = 0;
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|')
	{
		if (str[1] == '|')
			return (syntax_error_unexpected_token_str("||"), 1);
		if (str[1] == '&')
			return (syntax_error_unexpected_token_str("|&"), 1);
		syntax_error_unexpected_token('|');
		return (1);
	}
	while (str[pos])
	{
		skip_quotes(str, &pos);
		if (str[pos] == '|')
		{
			if (handle_pipe_syntax(str, &pos))
				return (1);
			continue ;
		}
		if (str[pos])
			pos++;
	}
	return (0);
}

int	precheck_and(char *str)
{
	if (str[0] == '&' || str[ft_strlen(str) - 1] == '&')
	{
		if (str[1] == '&')
			return (syntax_error_unexpected_token_str("&&"), 1);
		syntax_error_unexpected_token('&');
		return (1);
	}
	return (0);
}

int	check_and_operator(char *str)
{
	int	pos;

	pos = 0;
	if (precheck_and(str))
		return (1);
	while (str[pos])
	{
		skip_quotes(str, &pos);
		if (str[pos] == '&')
		{
			if (!str[pos + 1] || str[pos + 1] != '&')
				return (syntax_error_unexpected_token('&'), 1);
			pos += 2;
			skip_spaces(str, &pos);
			if (str[pos] == '|' || str[pos] == '&' || str[pos] == ')')
				return (syntax_error_unexpected_token(str[pos]), 1);
			continue ;
		}
		if (str[pos])
			pos++;
	}
	return (0);
}
