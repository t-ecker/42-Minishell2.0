#include "../../includes/minishell.h"

// checks if we have a group ()
// if so parse it from the very beginning
// if not, just parse a cmd

t_astNode	*parse_group(t_parser *p)
{
	t_astNode	*inner;
	t_astNode	*group_node;

	if (check_token_type(p, TOKEN_LPAREN))
	{
		advance_token(p);
		inner = parse_logical(p);
		advance_token(p);
		group_node = create_ast_node(AST_GROUP, p);
		group_node->u_data.group.child = inner;
		return (group_node);
	}
	return (parse_cmd(p));
}
