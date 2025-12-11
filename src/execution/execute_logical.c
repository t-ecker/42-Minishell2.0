#include "../../includes/minishell.h"

int	execute_logical(t_shell *shell, t_ast_node *node)
{
	int	left_res;

	left_res = execute(shell, node->u_data.logical_op.left);
	if (node->u_data.logical_op.op_type == LOG_OP_AND)
	{
		if (left_res != 0)
			return (left_res);
	}
	else if (node->u_data.logical_op.op_type == LOG_OP_OR)
	{
		if (left_res == 0)
			return (left_res);
	}
	return (execute(shell, node->u_data.logical_op.right));
}
