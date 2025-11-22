# include "../../includes/minishell.h"


void syntax_error_unexpected_token(char c)
{
	ft_putstr_fd(SYNTAX_ERROR, 2);
	ft_putstr_fd(" near unexpected token `", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("'", 2);
}

void syntax_error(char *str)
{
	ft_putstr_fd(SYNTAX_ERROR, 2);
	ft_putendl_fd(str, 2);
}

void fatal_error(t_shell *shell, char *msg)
{
	// free_env(shell->env);
	free_shell(shell);
	ft_putstr_fd(FATAL_ERROR, 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}