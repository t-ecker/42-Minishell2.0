#ifndef ENV_H
# define ENV_H

typedef struct s_shell	t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

char	*get_env_var(char *var_name, t_shell *shell);
char	**env_list_to_array(t_shell *shell);
void	create_env_list(t_shell *shell, char **envp);
void	add_env_node(t_shell *shell, char *key, char *value);
void	get_key_value(t_shell *shell, char *env_entry, \
			char **key, char **value);
void	delete_env_var(char *var_name, t_shell *shell);

#endif