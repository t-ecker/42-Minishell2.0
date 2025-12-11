#include "../../includes/minishell.h"

bool	clean_delimiter(char **delimiter, t_shell *shell)
{
	int		i;
	bool	expand;

	i = 0;
	expand = true;
	while ((*delimiter)[i])
	{
		if ((*delimiter)[i] == '\'' || (*delimiter)[i] == '"')
			expand = false;
		++i;
	}
	*delimiter = remove_quotes(*delimiter, shell);
	return (expand);
}

bool	read_heredoc(int fd, char *target, t_shell *shell)
{
	char	*line;
	size_t	del_len;
	bool	expand;
	int		stdin_backup;

	g_signal_received = 0;
	stdin_backup = dup(STDIN_FILENO);
	setup_heredoc_signals();
	expand = clean_delimiter(&target, shell);
	del_len = ft_strlen(target);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (handle_readline_error(stdin_backup, target), false);
		gc_add(shell, line);
		if (ft_strncmp(line, target, del_len) == 0 && line[del_len] == '\0')
			break ;
		if (expand)
			line = expand_var(line, shell);
		ft_putendl_fd(line, fd);
	}
	close(stdin_backup);
	return (setup_main_signals(), true);
}

bool	handle_heredoc(t_redirectList *redir, t_shell *shell)
{
	char	*filename;
	int		fd;
	bool	success;

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

bool	check_heredoc(t_ast_node *node, t_shell *shell)
{
	t_redirectList	*redir;

	redir = node->u_data.command.redirects;
	while (redir)
	{
		if (!handle_heredoc(redir, shell))
			return (false);
		redir = redir->next;
	}
	return (true);
}

bool	execute_heredoc(t_shell *shell, t_ast_node *node)
{
	t_pipelineList	*pipe;

	if (!node)
		return (true);
	if (node->type == AST_COMMAND)
		return (check_heredoc(node, shell));
	else if (node->type == AST_PIPE)
	{
		pipe = node->u_data.pipeline.commands;
		while (pipe)
		{
			if (!execute_heredoc(shell, pipe->command))
				return (false);
			pipe = pipe->next;
		}
	}
	else if (node->type == AST_LOGICAL_OP)
	{
		if (!execute_heredoc(shell, node->u_data.logical_op.left)
			|| !execute_heredoc(shell, node->u_data.logical_op.right))
			return (false);
	}
	else if (node->type == AST_GROUP)
		return (execute_heredoc(shell, node->u_data.group.child));
	return (true);
}
