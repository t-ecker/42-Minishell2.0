#include "../../includes/minishell.h"

// this is the start. first it parses left side of
	// logical op (cmd (redir)(pipe))
// then if there is a logical operator it parses right side.
// combiens left and right into a logical node with the correct op_type

t_astNode	*parse_logical(t_parser *p)
{
	t_astNode		*left;
	t_astNode		*right;
	t_astNode		*logical_node;
	t_logicalOpType	op_type;

	left = parse_pipe(p);
	while (check_token_type(p, TOKEN_AND) || check_token_type(p, TOKEN_OR))
	{
		if (p->current_token->type == TOKEN_AND)
			op_type = LOG_OP_AND;
		else
			op_type = LOG_OP_OR;
		advance_token(p);
		right = parse_pipe(p);
		logical_node = create_ast_node(AST_LOGICAL_OP, p);
		logical_node->u_data.logical_op.op_type = op_type;
		logical_node->u_data.logical_op.left = left;
		logical_node->u_data.logical_op.right = right;
		left = logical_node;
	}
	return (left);
}
