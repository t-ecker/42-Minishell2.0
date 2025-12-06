#include "../../includes/minishell.h"

char *generate_heredoc_filename(t_shell *shell)
{
	char *res;

	res = gc_add(shell, ft_itoa(shell->heredoc_counter++));
	res = gc_add(shell, ft_strjoin("/tmp/.heredoc_", res));
	return (res);
}

bool clean_delimiter(char **delimiter, t_shell *shell)
{
	int i;
	bool expand;

	i = 0;
	expand = true;
	while((*delimiter)[i])
	{
		if ((*delimiter)[i] == '\'' || (*delimiter)[i] == '"')
			expand = false;
		++i;
	}
	*delimiter = remove_quotes(*delimiter, shell);
	return (expand);
}

bool read_heredoc(int fd, char *target, t_shell *shell)
{
	char *line;
	size_t del_len;
	bool expand;
	int stdin_backup;

	g_signal_received = 0;
	stdin_backup = dup(STDIN_FILENO);
	setup_heredoc_signals();
	expand = clean_delimiter(&target, shell);
	del_len = ft_strlen(target);
	while(1)
	{
		line = readline("> ");
		if (!line)
		{
			dup2(stdin_backup, STDIN_FILENO);
            close(stdin_backup);
			if (g_signal_received != SIGINT)
			{
				ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
				ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
				ft_putstr_fd(target, STDERR_FILENO);
				ft_putendl_fd("')", STDERR_FILENO);
			}
			return (setup_main_signals(), false);
		}
		gc_add(shell, line);
		if (ft_strncmp(line, target, del_len) == 0 && line[del_len] == '\0')
			break;
		if (expand)
			expander(&line, shell, false);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(stdin_backup);
	return (setup_main_signals(), true);
}

bool handle_heredoc(t_redirectList *redir, t_shell *shell)
{
	char *filename;
	int fd;
	bool success;

	if (redir->type != REDIR_HEREDOC)
		return (true);
	filename = generate_heredoc_filename(shell);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (false);
	success = read_heredoc(fd, redir->target, shell);
	close(fd);
	if (!success)
	{
		unlink(filename);
		return (false);
	}
	redir->target = filename;
	return (true);
}

bool	check_heredoc(t_astNode *node, t_shell *shell)
{
	t_redirectList *redir;

	redir = node->u_data.command.redirects;
	while(redir)
	{
		if (!handle_heredoc(redir, shell))
			return (false);
		redir = redir->next;
	}
	return (true);
}

bool execute_heredoc(t_astNode *node, t_shell *shell)
{
	t_pipelineList *pipe;

	if (!node)
		return (true);
	if (node->type == AST_COMMAND)
		return (check_heredoc(node, shell));
	else if (node->type == AST_PIPE)
	{
		pipe = node->u_data.pipeline.commands;
		while (pipe)
		{
			if (!execute_heredoc(pipe->command, shell))
				return (false);
			pipe = pipe->next;
		}
	}
	else if (node->type == AST_LOGICAL_OP)
	{
		if (!execute_heredoc(node->u_data.logical_op.left, shell) 
			|| !execute_heredoc(node->u_data.logical_op.right, shell))
			return (false);
	}
	else if(node->type == AST_GROUP)
		return (execute_heredoc(node->u_data.group.child, shell));
	return (true);
}