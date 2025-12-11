#include "../../includes/minishell.h"

t_redirectList	*create_redir_node(t_redirectType type, char *target, \
		t_parser *p)
{
	t_redirectList	*node;

	node = gc_malloc(p->shell, sizeof(t_redirectList));
	node->type = type;
	node->target = gc_add(p->shell, ft_strdup(target));
	node->next = NULL;
	return (node);
}

void	add_redir_node(t_redirectList **head, t_redirectType type, \
		char *target, t_parser *p)
{
	t_redirectList	*node;
	t_redirectList	*current_node;

	node = create_redir_node(type, target, p);
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

t_redirectType	get_redir_type(t_tokenType type)
{
	if (type == TOKEN_APPEND_OUT)
		return (REDIR_APPEND);
	if (type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	if (type == TOKEN_REDIRECT_IN)
		return (REDIR_INPUT);
	else
		return (REDIR_OUTPUT);
}

void	handle_redirection(t_redirectList **head, t_parser *p)
{
	t_redirectType	redir_type;

	redir_type = get_redir_type(p->current_token->type);
	advance_token(p);
	add_redir_node(head, redir_type, p->current_token->value, p);
}
