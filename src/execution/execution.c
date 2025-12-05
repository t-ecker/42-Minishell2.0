#include "../../includes/minishell.h"

void get_backup_fds(t_executor *e)
{
	e->stdin_backup = dup(STDIN_FILENO);
	e->stdout_backup = dup(STDOUT_FILENO);
	if (e->stdin_backup == -1 || e->stdout_backup == -1)
		fatal_error(e->shell, DUP_ERROR);
}

void restore_fds(t_executor *e)
{
	if (dup2(e->stdin_backup, STDIN_FILENO) == -1 || dup2(e->stdout_backup, STDOUT_FILENO) == -1)
		fatal_error(e->shell, DUP_ERROR);
	close(e->stdin_backup);
	close(e->stdout_backup);
}

int execute(t_shell *shell, t_astNode *node)
{
	t_executor e;
	int res;

	e.shell = shell;
	get_backup_fds(&e);

	res = 0;
	if (node->type == AST_COMMAND)
		res = execute_cmd(&e, node);
	// else if (node->type == AST_PIPE)
	// 	res = execute_pipe(&e, node);
	// else if (node->type == AST_LOGICAL_OP)
	// 	res = execute_logical(&e, node);
	// else if (node->type == AST_GROUP)
	// 	res = execute(shell, node->u_data.group.child);
	restore_fds(&e);
	shell->exit_code = res;
	return (res);
}