#include "../../includes/minishell.h"

t_argList	*expand_args(t_shell *shell, t_argList *args)
{
	t_argList	*expanded;
	t_argList	*res;
	t_argList	*last;

	res = NULL;
	last = NULL;
	while (args)
	{
		expanded = expander(args->value, shell);
		if (!res)
		{
			res = expanded;
			last = res;
		}
		else
			last->next = expanded;
		while (last && last->next)
			last = last->next;
		args = args->next;
	}
	return (res);
}

char	**args_to_array(t_shell *shell, t_ast_node *node)
{
	t_argList	*expanded_words;
	t_argList	*current;
	char		**array;
	int			size;
	int			i;

	i = 0;
	size = 0;
	expanded_words = expand_args(shell, node->u_data.command.args);
	if (!expanded_words)
		return (NULL);
	current = expanded_words;
	while (current && ++size)
		current = current->next;
	array = gc_malloc(shell, sizeof(char *) * (size + 1));
	current = expanded_words;
	while (current)
	{
		array[i] = current->value;
		++i;
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

int	get_exit_code(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			ft_putendl_fd("", 2);
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit", 2);
		return (128 + sig);
	}
	return (0);
}

void	update_underscore(t_shell *shell, char **args, char *path)
{
	int		i;
	char	*last_arg;

	i = 0;
	while (args[i])
		++i;
	if (i > 1)
		last_arg = args[i - 1];
	else
		last_arg = path;
	add_env_node(shell, ft_strdup("_"), ft_strdup(last_arg));
}
