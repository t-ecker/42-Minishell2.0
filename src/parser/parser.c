# include "../../includes/minishell.h"

// utils -----
t_astNode *create_astNode(t_astNodeType type, t_parser *p)
{
	t_astNode *node;
	
	node = gc_malloc(p->shell, sizeof(t_astNode));
	node->type = type;
	ft_memset(&node->u_data, 0, sizeof(node->u_data));
	return (node);
}

void advance_token(t_parser *p)
{
	if (p->current_token)
		p->current_token = p->current_token->next;
}

bool check_token_type(t_parser *p, t_tokenType type)
{
	return (p->current_token && p->current_token->type == type);
}
// -----

// recursive descent parser
// parser assumes valid syntax (checked by validator)

// PRECEDENCE:
// - Redirects and arguments
// - Pipes
// - Logical OR / AND

void parser(t_shell *shell)
{
	t_parser p;
	
	p.shell = shell;
	p.current_token = shell->tokens.head;

	shell->ast = parse_logical(&p);
}