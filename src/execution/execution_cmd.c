#include "../../includes/minishell.h"

char **args_to_array(t_shell *shell, t_astNode *node)
{
	t_argList *list;
	t_argList *current;
	char **array;
	int size;
	int i;
	int len;

	i = 0;
	size = 0;
	list = node->u_data.command.args;
	if (!list)
		return NULL;
	current = list;
	while(current)
	{
		++size;
		current = current->next;
	}
	array = gc_malloc(shell, sizeof(char *) * (size + 1));
	current = list;
	while(current)
	{
		expander(&current->value, shell, true);
		len = ft_strlen(current->value);
		array[i] = gc_malloc(shell, len + 1);
		ft_strlcpy(array[i], current->value, len + 1);
		current = current->next;
		++i;
	}
	array[i] = NULL;
	return (array);
}

int execute_cmd(t_executor *e, t_astNode *node)
{
	char **args;

	args = args_to_array(e->shell, node);
	return (get_exit_code(status));
}
