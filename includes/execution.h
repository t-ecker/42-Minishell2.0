#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_executor
{
	t_shell	*shell;
	int		exit_code;
	int		stdin_backup;
	int		stdout_backup;
}	t_executor;

typedef enum s_builtin_type
{
	NONE,
	EXIT,
	PWD,
	CD,
	ENV,
	EXPORT,
	UNSET,
	ECHOO
}	t_builtin_type;

int execute(t_shell *shell, t_astNode *node);
int execute_cmd(t_executor *e, t_astNode *node);

#endif