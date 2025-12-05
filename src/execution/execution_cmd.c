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

int get_cmd_path(char *cmd, t_executor *e, char **path)
{
	if (ft_strchr(cmd, '/'))
		*path = cmd;
	else
		*path = search_in_path(cmd, e);
	return(validate_path(*path, cmd));
}

int execute_cmd(t_executor *e, t_astNode *node)
{
	char **args;
    char *path;
    int pid;
    int status;
    int code;

	args = args_to_array(e->shell, node);
    code = get_cmd_path(args[0], e, &path);
	if (code)
		return (code);
	pid = fork();
	if (pid < 0)
		fatal_error(e->shell, FORK_ERROR);
	if (pid == 0)
	{
		setup_child_signals();
		execve(path, args, e->shell->env);
		// ft_putendl_fd("aa", 2);
		execution_error(strerror(errno), args[0]);
		if (errno == ENOENT)
            exit(127);
		exit(126);
	}
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}
