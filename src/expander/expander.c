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

void init_expander(t_expand *e, t_shell *shell)
{
	e->capacity = 10;
	e->res = gc_malloc(shell, e->capacity);
	e->res[0] = '\0';
	e->shell = shell;
	e->insideDoubleQuote = false;
	e->insideSingleQuote = false;
}

void expander(char **str, t_shell *shell, bool exp_wilcards)
{
	t_argList *args;
	char *res;

	res = expand_var(*str, shell);
	args = word_split(res, shell);
	if (exp_wilcards)
		args = expand_wildcard(args, shell);
	remove_quotes_from_list(args, shell);
	// print_argList(args)
}