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
	if (ft_strncmp(str, SYNTAX_QUOTE_ERROR, ft_strlen(SYNTAX_QUOTE_ERROR)))
		ft_putstr_fd(SYNTAX_ERROR, 2);
	ft_putendl_fd(str, 2);
}

void execution_error(char *str, char *cmd)
{
	ft_putstr_fd(MINISHELL_BASE, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
}

void export_error(char c)
{
	ft_putstr_fd(MINISHELL_BASE, 2);
	ft_putstr_fd("export: `", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}


//needs to free everything at any time
void fatal_error(t_shell *shell, char *msg)
{
	gc_free_all(shell);
	free_env(shell);
	ft_putstr_fd(FATAL_ERROR, 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}