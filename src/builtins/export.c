# include "../../includes/minishell.h"

bool check_key(char *key)
{
	int i;

	if (!key || !*key)
		return (export_error('='), false);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (export_error(key[0]), false);
	i = 1;
	while(key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (export_error(key[i]), false);
		++i;
	}
	return (true);
}

int ft_export(char **args, t_shell *shell)
{
	t_env *current;
	int i;
	char *key;
	char *value;

	if (args[1] == NULL)
	{
		current = shell->env_list;
		while(current)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->key, 1);
			if (current->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(current->value, 1);
				ft_putchar_fd('"', 1);
			}
			ft_putendl_fd("", 1);
			current = current->next;
		}
	}
	else
	{
		i = 1;
		while(args[i])
		{
			get_key_value(shell, args[i], &key, &value);
			if (!check_key(key))
				return (free(key), free(value), 1);
			add_env_node(shell, key, value);
			++i;
		}
	}
	return (0);
}
