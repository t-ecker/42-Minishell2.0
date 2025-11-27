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
	// shell->tokens = NULL;
}

// all allocations inside the loop are stored inside a garbageCollector so that its easier to free (especially on errors)
// but all persistant data like env must be freed normally

void loop(t_shell *shell)
{
	while(1)
	{
		reset(shell);
		// set_signals (maybe)
		get_input(shell);
		if (input_validation(shell))
		{
			gc_free_all(shell);
			ft_putendl_fd("valid input: ❌", 1); //debug
			continue ;
		}
		if (!ft_strncmp(shell->input, "exit", ft_strlen(shell->input)))
		{
			gc_free_all(shell);
			break;
		}
		lexer(shell);
		print_tokens(shell->tokens); //debug
		parser(shell);
		print_ast(shell->ast, 0);
		// execute(shell);
		expander(&shell->input, shell);
		ft_putendl_fd(shell->input, 1);
		gc_free_all(shell);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	
	ft_memset(&shell, 0, sizeof(t_shell));
	check_args(argc, argv, envp);
	// TODO:
	// create_env(&shell, envp);
	// update_shellLVL(&shell);
	loop(&shell);
	// free_env();
	return(0);
}