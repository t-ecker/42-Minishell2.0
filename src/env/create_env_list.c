# include "../../includes/minishell.h"

t_env *create_env_node(t_shell *shell, char *key, char *value)
{
	t_env *node;
	t_env *current;

	current = shell->env_list;
	while(current)
	{
		if (ft_strncmp(key, current->key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(current->key))
		{
			free(current->value);
			current->value = value;
			return (free(key), NULL);
		}
		current = current->next;
	}
	node = malloc(sizeof(t_env));
	if (!node)
	{
		free(key);
		free(value);
		fatal_error(shell, MALLOC_ERROR);
	}
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void add_env_node(t_shell *shell, char *key, char *value)
{
	t_env *node;
	t_env *current_node;
	
	if (!key) //correct?
	{
		if (value)
			free(value);
		fatal_error(shell, MALLOC_ERROR);
	}
	node = create_env_node(shell, key, value);
	if (!node)
		return ;
	if (shell->env_list == NULL)
		shell->env_list = node;
	else
	{
		current_node = shell->env_list;
		while(current_node->next)
			current_node = current_node->next;
		current_node->next = node;
	}
}

void update_shlvl(t_shell *shell, char *key, char **value)
{
	int original_value;
	char *tmp;

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

void get_key_value(t_shell *shell, char *env_entry, char **key, char **value)
{
	char *equal_sign;
	equal_sign = ft_strchr(env_entry, '=');
	if (env_entry[0] != '=' && equal_sign)
	{
		*key = ft_substr(env_entry, 0, equal_sign - env_entry);
		if (!*key)
			fatal_error(shell, MALLOC_ERROR);
		*value = ft_strdup(equal_sign + 1);
		if (!*value)
		{
			free(*key);
			fatal_error(shell, MALLOC_ERROR);
		}
	}
	else
	{
		*key = ft_strdup(env_entry);
		if (!*key)
			fatal_error(shell, MALLOC_ERROR);
		*value = NULL;
	}
}

void check_env(t_shell *shell)
{
	if (!get_env_var("PWD", shell))
		add_env_node(shell, ft_strdup("PWD"), getcwd(NULL, 0));
	if (!get_env_var("SHLVL", shell))
		add_env_node(shell, ft_strdup("SHLVL"), ft_strdup("1"));
}

void create_env_list(t_shell *shell, char **envp)
{
	int i;
	char *key;
	char *value;

	i = -1;
	while(envp[++i])
	{
		get_key_value(shell, envp[i], &key, &value);
		if (value && ft_strncmp(key, "SHLVL", ft_strlen(key)) == 0 && ft_strlen(key) == 5)
			update_shlvl(shell, key, &value);
		add_env_node(shell, key, value);
	}
	check_env(shell);
}

