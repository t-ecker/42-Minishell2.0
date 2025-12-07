# include "../../includes/minishell.h"

void free_env(t_shell *shell)
{
	t_env *current;
	t_env *next;

	current = shell->env_list;
	while(current)
	{
		free(current->key);
		free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
}

void free_all(t_shell *shell)
{
	gc_free_all(shell);
	free_env(shell);
}