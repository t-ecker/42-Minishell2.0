#include "../../includes/minishell.h"

void	syntax_error_unexpected_token_str(char *c)
{
	ft_putstr_fd(SYNTAX_ERROR, 2);
	ft_putstr_fd(" near unexpected token `", 2);
	ft_putstr_fd(c, 2);
	ft_putendl_fd("'", 2);
}

void	syntax_error_unexpected_token(char c)
{
	ft_putstr_fd(SYNTAX_ERROR, 2);
	ft_putstr_fd(" near unexpected token `", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("'", 2);
}

void	syntax_error(char *str)
{
	if (ft_strncmp(str, SYNTAX_QUOTE_ERROR, ft_strlen(SYNTAX_QUOTE_ERROR)))
		ft_putstr_fd(SYNTAX_ERROR, 2);
	ft_putendl_fd(str, 2);
}
