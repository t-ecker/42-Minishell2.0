#include "../../includes/minishell.h"

int execute(t_shell *shell, t_astNode *node)
{
	t_executor e;
	int res;

	e.shell = shell;

	res = 0;
	if (node->type == AST_COMMAND)
		res = execute_cmd(&e, node);
	shell->exit_code = res;
	return (res);
}