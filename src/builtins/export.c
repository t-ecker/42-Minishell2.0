# include "../../includes/minishell.h"

bool check_key(char *key)
{
	int i;

	if (!key || !*key)
		return (false);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (false);
	i = 1;
	while(key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
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
	int exit_code;

	exit_code = 0;
	if (args[1] == NULL)
	{
		current = shell->env_list;
		while(current)
		{
			if (!(current->key[0] == '_' && !current->key[1]))
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
			}
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
			{
				export_error_str(args[i]);
				exit_code = 1;
				free(key);
				free(value);
			}
			else
				add_env_node(shell, key, value);
			++i;
		}
	}
	return (exit_code);
}
