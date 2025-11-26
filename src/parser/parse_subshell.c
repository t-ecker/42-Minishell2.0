# include "../../includes/minishell.h"

// checks if we have a subshell ()
// if so parse it from the very beginning
// if not, just parse a cmd

t_astNode *parse_subshell(t_parser *p)
{
	t_astNode *inner;
	t_astNode *subshell_node;

	if (check_token_type(p, TOKEN_LPAREN))
	{
		advance_token(p);
		inner = parse_logical(p);
		// check for r_par?
		advance_token(p);
		subshell_node = create_astNode(AST_SUBSHELL, p);
		subshell_node->u_data.subshell.child = inner;
		return (subshell_node);
	}
	return (parse_cmd(p));
}