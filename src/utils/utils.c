# include "../../includes/minishell.h"


void exit_code(t_shell *shell, int code)
{
	shell->exit_code = code;
}

bool is_special_char(char c) {
    return c == '|' || c == '&' || c == '(' || c == ')' || 
           c == '<' || c == '>';
}

void skip_quotes(char *str, int *pos)
{
	char quote;

	if (str[*pos] == '\'' || str[*pos] == '"')
	{
		quote = str[(*pos)++];
		while(str[*pos] && str[*pos] != quote)
			(*pos)++;
		if (str[*pos] == quote)
            (*pos)++;
	}
}

void skip_spaces(char *str, int *pos)
{
	while(str[*pos] && ft_isspace(str[*pos]))
		(*pos)++;
}

void toggleBool(bool *input)
{
	*input = !(*input);
}

void toggle_quote(char c, bool *openDoubleQuote, bool *openSingleQuote)
{
	if (c == '\'' && !*openDoubleQuote)
		toggleBool(openSingleQuote);
	else if (c == '"' && !*openSingleQuote)
		toggleBool(openDoubleQuote);
}

char *remove_quotes(char *str, t_shell *shell)
{
	int pos;
	t_expand e;
	char quote;

	init_expander(&e, shell);
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] =='"')
		{
			quote = str[pos++];
			while(str[pos] && str[pos] != quote)
				append_char(str[pos++], &e);
			if (str[pos] == quote)
				++pos;
		}
		else
			append_char(str[pos++], &e);
	}
	return (e.res);
}
