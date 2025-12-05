#include "../../includes/minishell.h"

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
	return (true);
}