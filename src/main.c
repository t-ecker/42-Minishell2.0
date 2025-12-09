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
	setup_main_signals();
	shell->input = NULL;
	// if (!is_cursor_at_col_one())
	// 		ft_putchar_fd('\n', STDOUT_FILENO);
}

// all allocations inside the loop are stored inside a garbageCollector so that its easier to free (especially on errors)
// but all persistant data like env must be freed normally

void loop(t_shell *shell)
{
	while(1)
	{
		reset(shell);
		if (get_input(shell))
			break;
		if (input_validation(shell))
		{
			gc_free_all(shell);
			shell->exit_code = 2;
			// ft_putendl_fd("valid input: ❌", 1); //debug
			continue ;
		}
		// if (!ft_strncmp(shell->input, "exit", ft_strlen(shell->input))) //must be removed later
		// {
		// 	gc_free_all(shell);
		// 	break;
		// }
		lexer(shell);
		// print_tokens(shell->tokens); //debug
		parser(shell);
		// print_ast(shell->ast, 0);
		if (!execute_heredoc(shell, shell->ast))
		{
			gc_free_all(shell);
			continue;
		}
		execute(shell, shell->ast);
		// if (isatty(STDOUT_FILENO))
		// 	ft_putchar_fd('\n', STDOUT_FILENO);
		gc_free_all(shell);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	
	ft_memset(&shell, 0, sizeof(t_shell));
	check_args(argc, argv, envp);
	// TODO:
	create_env_list(&shell, envp);
	// create_env(&shell, envp);
	// update_shellLVL(&shell);
	loop(&shell);
	free_env(&shell);
	return(0);
}