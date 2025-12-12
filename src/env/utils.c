/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:11:17 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:11:18 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	update_shlvl(t_shell *shell, char *key, char **value)
{
	int		original_value;
	char	*tmp;

	original_value = ft_atoi(*value);
	if (original_value > 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(original_value, 2);
		ft_putendl_fd(") too high, resetting to 1", 2);
	}
	if (!original_value || original_value < 0 || original_value > 1000)
		original_value = 0;
	tmp = ft_itoa(original_value + 1);
	free(*value);
	if (!tmp)
	{
		free(key);
		fatal_error(shell, MALLOC_ERROR);
	}
	*value = tmp;
}
