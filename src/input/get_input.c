# include "../../includes/minishell.h"

int get_input(t_shell *shell)
{
	shell->input = readline("minishell: ");
	if (!shell->input)
		return (1);
	if (shell->input[0] != '\0')
		add_history(shell->input);
	return (0);
}