# include "../../includes/minishell.h"

void append_char(char c, t_expand *e)
{
	size_t res_len;

	res_len = ft_strlen(e->res);
	if (res_len + 2 >= e->capacity)
	{
		e->capacity *= 2;
		e->res = gc_realloc(e->shell, e->res, e->capacity, res_len + 1);
	}
	e->res[res_len] = c;
	e->res[res_len + 1] = '\0';
}

void append_str(char *str, t_expand *e)
{
	int i;

	i = 0;
	while(str[i])
	{
		append_char(str[i], e);
		++i;
	}
}

t_expand *create_expander(t_shell *shell)
{
	t_expand *e;

	e = gc_malloc(shell, sizeof(t_expand));
	e->capacity = 10;
	e->res = gc_malloc(shell, e->capacity);
	e->res[0] = '\0';
	e->shell = shell;
	e->insideDoubleQuote = false;
	e->insideSingleQuote = false;
	return (e);
}

void expander(char **str, t_shell *shell)
{
	*str = expand_var(*str, shell);
	// *str = expand_wildcards(*str, shell);
	// *str = remove_quotes(*str, shell);
}