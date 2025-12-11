#include "../../includes/minishell.h"

t_argList	*create_args_node(char *value, t_shell *shell)
{
	t_argList	*node;

	node = gc_malloc(shell, sizeof(t_argList));
	node->value = gc_add(shell, ft_strdup(value));
	node->next = NULL;
	return (node);
}

void	add_arg_node(t_argList **head, char *value, t_shell *shell)
{
	t_argList	*node;
	t_argList	*current_node;

	node = create_args_node(value, shell);
	if (*head == NULL)
		*head = node;
	else
	{
		current_node = *head;
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = node;
	}
}

bool	is_redir_token(t_tokenType type)
{
	return (type == TOKEN_APPEND_OUT || type == TOKEN_HEREDOC
		|| type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT);
}

// until there is something else than a redir or word token parse into one
	// cmd node that has an args list and an redir list
// redirList stores all redirs in this block after another.
// argList stores all args after another

t_astNode	*parse_cmd(t_parser *p)
{
	t_astNode	*command_node;

	command_node = create_ast_node(AST_COMMAND, p);
	while (p->current_token && p->current_token->type != TOKEN_EOF)
	{
		if (is_redir_token(p->current_token->type))
			handle_redirection(&command_node->u_data.command.redirects, p);
		else if (p->current_token->type == TOKEN_WORD)
			add_arg_node(&command_node->u_data.command.args, \
				p->current_token->value, p->shell);
		else
			break ;
		advance_token(p);
	}
	return (command_node);
}
