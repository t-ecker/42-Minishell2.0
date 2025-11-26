# include "../../includes/minishell.h"

int get_input(t_shell *shell)
{
	shell->input = readline("minishell: ");
	if (!shell->input)
		fatal_error(shell, READLINE_ERROR); //CHECK: maybe too hard error handling (ctrl d)
	gc_add(shell, shell->input);
	if (shell->input[0] != '\0')
		add_history(shell->input);
	return (0);
}