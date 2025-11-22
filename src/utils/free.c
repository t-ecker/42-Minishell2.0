# include "../../includes/minishell.h"


void free_shell(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
}

// void free_env(idk)
