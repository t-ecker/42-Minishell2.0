#include "../../includes/minishell.h"

int	ft_env(char **args, t_shell *shell)
{
	t_env	*current;

	if (args[1] == NULL)
	{
		add_env_node(shell, ft_strdup("_"), ft_strdup("env"));
		current = shell->env_list;
		while (current)
		{
			if (current->value)
			{
				ft_putstr_fd(current->key, 1);
				ft_putstr_fd("=", 1);
				ft_putendl_fd(current->value, 1);
			}
			current = current->next;
		}
		return (0);
	}
	else
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
		return (1);
	}
}
