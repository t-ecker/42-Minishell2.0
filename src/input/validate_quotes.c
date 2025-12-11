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
