#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_executor
{
	t_shell	*shell;
	int		exit_code;
	int		stdin_backup;
	int		stdout_backup;
}	t_executor;

int execute(t_shell *shell, t_astNode *node);


#endif