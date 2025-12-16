#include "../../includes/minishell.h"

t_builtin_type	is_buildin(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "echo", len) == 0 && len == 4)
		return (ECHOO);
	if (ft_strncmp(cmd, "cd", len) == 0 && len == 2)
		return (CD);
	if (ft_strncmp(cmd, "pwd", len) == 0 && len == 3)
		return (PWD);
	if (ft_strncmp(cmd, "export", len) == 0 && len == 6)
		return (EXPORT);
	if (ft_strncmp(cmd, "unset", len) == 0 && len == 5)
		return (UNSET);
	if (ft_strncmp(cmd, "env", len) == 0 && len == 3)
		return (ENV);
	if (ft_strncmp(cmd, "exit", len) == 0 && len == 4)
		return (EXIT);
	return (NONE);
}

int	execute_buildin(t_shell *shell, char **args, t_builtin_type type)
{
	int		res;

	res = 1;
	if (type == ECHOO)
		res = ft_echo(args);
	else if (type == CD)
		res = ft_cd(args, shell);
	else if (type == PWD)
		res = ft_pwd(shell);
	if (type == EXPORT)
		res = ft_export(args, shell);
	else if (type == UNSET)
		res = ft_unset(args, shell);
	else if (type == ENV)
		res = ft_env(args, shell);
	else if (type == EXIT)
		res = ft_exit(args, shell);
	update_underscore(shell, args, args[0]);
	return (res);
}

void	execute_external_cmd(char *path, char **args,
		char **env)
{
	execve(path, args, env);
	execution_error(strerror(errno), args[0]);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

int	execute_external(t_shell *shell, char **args, char **env,
		bool exec_in_child)
{
	int		code;
	char	*path;
	int		pid;
	int		status;

	code = get_cmd_path(args[0], shell, &path);
	if (code)
		return (code);
	update_underscore(shell, args, path);
	if (!exec_in_child)
		execute_external_cmd(path, args, env);
	pid = fork();
	if (pid < 0)
		fatal_error(shell, FORK_ERROR);
	if (pid == 0)
	{
		setup_child_signals();
		execute_external_cmd(path, args, env);
	}
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}

int	execute_cmd(t_shell *shell, t_ast_node *node, bool exec_in_child)
{
	char			**args;
	char			**env;
	t_builtin_type	builtin;

	args = args_to_array(shell, node);
	env = env_list_to_array(shell);
	if (handle_redirections(shell, node->u_data.command.redirects))
		return (1);
	if (!args || !args[0])
		return (0);
	g_signal_received = 0;
	if (exec_in_child)
		signal(SIGINT, SIG_IGN);
	builtin = is_buildin(args[0]);
	if (builtin != NONE)
		return (execute_buildin(shell, args, builtin));
	return (execute_external(shell, args, env, exec_in_child));
}
