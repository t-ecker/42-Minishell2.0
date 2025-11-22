# include "../../includes/minishell.h"


void exit_code(t_shell *shell, int code)
{
	shell->exit_code = code;
}