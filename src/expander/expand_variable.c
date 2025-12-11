#include "../../includes/minishell.h"

int	extract_var_name(char *start, char **var_name, t_shell *shell)
{
	int	len;

	len = 0;
	while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
		++len;
	if (len == 0)
		return (0);
	*var_name = gc_malloc(shell, len + 1);
	ft_memcpy(*var_name, start, len);
	(*var_name)[len] = '\0';
	return (len);
}

void	handle_var(char *str, int *pos, t_expand *e)
{
	char	*var_name;
	int		var_len;
	char	*value;

	var_len = extract_var_name(&str[*pos], &var_name, e->shell);
	if (var_len > 0)
	{
		value = get_env_var(var_name, e->shell);
		if (value)
			append_str(value, e);
		*pos += var_len;
	}
	else
		append_char('$', e);
}

int	handle_dollar_sign(t_shell *shell, char *str, t_expand *e, int *pos)
{
	++(*pos);
	if (str[*pos] == '?')
		append_str(gc_add(shell, ft_itoa(shell->exit_code)), e);
	else if (str[*pos] == '0')
		append_str(gc_add(shell, ft_strdup("minishell")), e);
	else
	{
		handle_var(str, pos, e);
		return (1);
	}
	return (0);
}

char	*expand_var(char *str, t_shell *shell)
{
	int			pos;
	t_expand	e;

	pos = 0;
	init_expander(&e, shell);
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '"')
		{
			toggle_quote(str[pos], &e.inside_double_quote, \
				&e.inside_single_quote);
			append_char(str[pos], &e);
		}
		else if (str[pos] == '$' && !e.inside_single_quote)
		{
			if (handle_dollar_sign(shell, str, &e, &pos))
				continue ;
		}
		else
			append_char(str[pos], &e);
		++pos;
	}
	return (e.res);
}
