# include "../../includes/minishell.h"

int check_quotes(char *str)
{
	int pos;
	bool openSingleQuote;
	bool openDoubleQuote;

	pos = 0;
	openDoubleQuote = false;
	openSingleQuote = false;
	while (str[pos])
	{
		toggle_quote(str[pos], &openDoubleQuote, &openSingleQuote);
		pos++;
	}
	if (openDoubleQuote || openSingleQuote)
		return (syntax_error(SYNTAX_QUOTE_ERROR), 1);
	return (0);
}