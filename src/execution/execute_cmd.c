#include "../../includes/minishell.h"

int execute_redirection(t_shell *shell, t_redirectList *node)
{
	int fd;
	t_argList *expanded_target;

	expanded_target = expander(node->target, shell);
	if (!expanded_target || !expanded_target->value || !expanded_target->value[0] || expanded_target->next)
		return(execution_error("ambiguous redirect", node->target), 1);
	if (node->type == REDIR_INPUT)
	{
		fd = open(expanded_target->value, O_RDONLY);
		if (fd == -1)
			return (execution_error(strerror(errno), expanded_target->value), 1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			fatal_error(shell, DUP_ERROR);
		}
		close(fd);
	}
	else if (node->type == REDIR_OUTPUT)
	{
		fd = open(expanded_target->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (execution_error(strerror(errno), expanded_target->value), 1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			fatal_error(shell, DUP_ERROR);
		}
		close(fd);
	}
	else if (node->type == REDIR_APPEND)
	{
		fd = open(expanded_target->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (execution_error(strerror(errno), expanded_target->value), 1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			fatal_error(shell, DUP_ERROR);
		}
		close(fd);
	}
	else if (node->type == REDIR_HEREDOC)
	{
		fd = open(expanded_target->value, O_RDONLY);
		if (fd == -1)
			return (execution_error(strerror(errno), expanded_target->value), 1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			fatal_error(shell, DUP_ERROR);
		}
		unlink(expanded_target->value);
		close(fd);
	}
	return (0);
}

int handle_redirections(t_shell *shell, t_redirectList *node)
{
	t_redirectList *current;

	current = node;
	while(current)
	{
		if (execute_redirection(shell, current))
			return (1);
		current = current->next;
	}
	return (0);
}

t_argList *expand_args(t_shell *shell, t_argList *args)
{
	t_argList *expanded;
	t_argList *res;
	t_argList *last;

	res = NULL;
	last = NULL;

	while(args)
	{
		expanded = expander(args->value, shell);
		if (!res)
		{
			res = expanded;
			last = res;
		}
		else
			last->next = expanded;
		while(last && last->next)
			last = last->next;
		args = args->next;
	}
	return (res);
}

char **args_to_array(t_shell *shell, t_astNode *node)
{
	t_argList *expanded_words;
	t_argList *current;
	char **array;
	int size;
	int i;

	i = 0;
	size = 0;
	expanded_words = expand_args(shell, node->u_data.command.args);
	if (!expanded_words)
		return NULL;
	current = expanded_words;
	while(current)
	{
		++size;
		current = current->next;
	}
	array = gc_malloc(shell, sizeof(char *) * (size + 1));
	current = expanded_words;
	while(current)
	{
		// if (current->value[0])
		// {
			array[i] = current->value;
			++i;
		// }
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

char *search_in_path(char *cmd, t_shell *shell)
{
	char *path;
	char **paths;
	char *full_path;
	int i;

	path = get_env_var("PATH", shell);
	if (!path)
		return (NULL);
	paths = gc_add(shell, ft_split(path, ':'));
	i = 0;
	while(paths[i])
		gc_add(shell, paths[i++]);
	i = 0;
	while(paths[i])
	{
		full_path = gc_add(shell, ft_strjoin(paths[i], "/"));
		full_path = gc_add(shell, ft_strjoin(full_path, cmd));
		if (access(full_path, X_OK) == 0)
			return(full_path);
		++i;
	}
	return (NULL);
}

int validate_path(char *path, char *cmd, bool is_absolute)
{
	struct stat st;

	if (!path || stat(path, &st) < 0)
	{
		if (is_absolute)
			return (execution_error(NO_SUCH_FILE_ERROR, cmd), 127);
		return (execution_error(CMD_NOT_FOUND_ERROR, cmd), 127);
	}
	if (S_ISDIR(st.st_mode))
		return (execution_error(IS_DIR_ERROR, path), 126);
	if (access(path, X_OK) < 0)
		return (execution_error(PERMISSION_ERROR, path), 126);
	return (0);
}


int get_cmd_path(char *cmd, t_shell *shell, char **path)
{
	bool is_absolute;

	is_absolute = (ft_strchr(cmd, '/') != NULL);
	if (is_absolute)
		*path = cmd;
	else
		*path = search_in_path(cmd, shell);
	return(validate_path(*path, cmd, is_absolute));
}

t_builtin_type is_buildin(char *cmd)
{
	size_t len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "echo", len) == 0 && len == 4)
		return (ECHOO);
	else if (ft_strncmp(cmd, "cd", len) == 0 && len == 2)
		return (CD);
	else if (ft_strncmp(cmd, "pwd", len) == 0 && len == 3)
		return (PWD);
	else if (ft_strncmp(cmd, "export", len) == 0 && len == 6)
		return (EXPORT);
	else if (ft_strncmp(cmd, "unset", len) == 0 && len == 5)
		return (UNSET);
	else if (ft_strncmp(cmd, "env", len) == 0 && len == 3)
		return (ENV);
	else if (ft_strncmp(cmd, "exit", len) == 0 && len == 4)
		return (EXIT);
	return (NONE);
}

int execute_buildin(t_shell *shell, char **args, t_builtin_type type)
{
	// ft_putendl_fd("execute builtin", 2);
	if (type == ECHOO)
		return (ft_echo(args));
	else if (type == CD)
		return (ft_cd(args, shell));
	else if (type == PWD)
		return (ft_pwd(shell));
	if (type == EXPORT)
		return (ft_export(args, shell));
	else if (type == UNSET)
		return (ft_unset(args, shell));
	else if (type == ENV)
		return (ft_env(args, shell));
	else if (type == EXIT)
		return (ft_exit(args, shell));
	return (1);
}

// does it print ^C???
// mac bash:
// if (sig == SIGINT)
// 	ft_putendl_fd("^C", 2);
// if (sig == SIGQUIT)
// 	ft_putendl_fd("^\\Quit: 3", 2);
int get_exit_code(int status)
{
	int sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			ft_putendl_fd("", 2);
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit", 2); //3 correct?? output depends on bash version
		return (128 + sig);
	}
	return 0;
}

int execute_cmd(t_shell *shell, t_astNode *node, bool exec_in_child)
{
	char **args;
	char **env;
	char *path;
	int pid;
	int status;
	int code;
	t_builtin_type builtin;
	
	args = args_to_array(shell, node);
	env = env_list_to_array(shell);
	if (handle_redirections(shell, node->u_data.command.redirects))
		return (1);
	// ft_putendl_fd(args[0], 1);
	if (!args || !args[0])
		return (0);
	g_signal_received = 0;
	signal(SIGINT, SIG_IGN);
	builtin = is_buildin(args[0]);
	if (builtin != NONE)
		return(execute_buildin(shell, args, builtin));
	code = get_cmd_path(args[0], shell, &path);
	if (code)
		return (code);
	if (!exec_in_child)
	{
		// ft_putendl_fd("execute without new fork", 2);
		execve(path, args, env);
		execution_error(strerror(errno), args[0]);
		if (errno == ENOENT)
            exit(127);
		exit(126);
	}
	pid = fork();
	if (pid < 0)
		fatal_error(shell, FORK_ERROR);
	if (pid == 0)
	{
		setup_child_signals();
		// ft_putendl_fd("execute inside new fork", 2);
		execve(path, args, env);
		execution_error(strerror(errno), args[0]);
		if (errno == ENOENT)
            exit(127);
		exit(126);
	}
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}
