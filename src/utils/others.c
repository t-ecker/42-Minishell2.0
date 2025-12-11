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
