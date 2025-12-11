#include "../../includes/minishell.h"

char	*get_env_var(char *var_name, t_shell *shell)
{
	t_env	*current;

	current = shell->env_list;
	while (current)
	{
		if (ft_strncmp(var_name, current->key, ft_strlen(var_name)) == 0
			&& ft_strlen(var_name) == ft_strlen(current->key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	delete_env_var(char *var_name, t_shell *shell)
{
	t_env	*current;
	t_env	*previous;

	current = shell->env_list;
	previous = NULL;
	while (current)
	{
		if (ft_strncmp(var_name, current->key, ft_strlen(var_name)) == 0
			&& ft_strlen(var_name) == ft_strlen(current->key))
		{
			if (!previous)
				shell->env_list = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

char	*join_env(t_shell *shell, t_env *current)
{
	char	*res;

	res = gc_add(shell, ft_strjoin(current->key, "="));
	res = gc_add(shell, ft_strjoin(res, current->value));
	return (res);
}

char	**env_list_to_array(t_shell *shell)
{
	char	**env_arr;
	t_env	*current;
	int		count;
	int		i;

	count = 0;
	current = shell->env_list;
	while (current)
	{
		if (current->value)
			count++;
		current = current->next;
	}
	env_arr = gc_malloc(shell, sizeof(char *) * (count + 1));
	i = 0;
	current = shell->env_list;
	while (current)
	{
		if (current->value)
			env_arr[i++] = join_env(shell, current);
		current = current->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
