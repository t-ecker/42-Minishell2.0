#include "../includes/minishell.h"

void check_args(int argc, char **argv, char **envp)
{
	(void)argv;

	if (argc != 1)
	{
		ft_putendl_fd("Invalid input", 2);
		exit(1);
	}
	// TODO:
	// check envp
	(void) envp;
}

void reset(t_shell *shell)
{
	shell->input = NULL;
	shell->exit_code = 0;
}

void loop(t_shell *shell)
{
	while(1)
	{
		reset(shell);
		// ?
		// set_signals
		if (get_input(shell))
			return ;
		if (input_validation(shell))
		{
			free_shell(shell);
			ft_putendl_fd("input: ❌", 1);
			continue ;
		}
		if (!ft_strncmp(shell->input, "exit", ft_strlen(shell->input)))
			return (free_shell(shell));
		// lexer(shell);
		// parser(shell);
		// execute(shell);
		// free_shell(shell);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	check_args(argc, argv, envp);
	// TODO:
	// create_env(&shell, envp);
	// update_shellLVL(&shell);
	loop(&shell);
	// free_env();
	return(0);
}