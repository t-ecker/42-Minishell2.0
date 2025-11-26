# include "../../includes/minishell.h"

int input_validation(t_shell *shell)
{
	shell->input = gc_add(shell, ft_strtrim(shell->input, " \t"));
	if (shell->input[0] == '\0')
		return (1);
	if (check_quotes(shell->input))
		return (exit_code(shell, 258), 1);
	if (check_pipes(shell->input))
		return (exit_code(shell, 258), 1);
	if (check_redir(shell->input))
		return (exit_code(shell, 258), 1);
	if (check_parentheses(shell->input))
		return (exit_code(shell, 258), 1);
	if (check_and_operator(shell->input))
		return (exit_code(shell, 258), 1);
	ft_putendl_fd("valid input: ✅", 1); //debug
	return (0);
}