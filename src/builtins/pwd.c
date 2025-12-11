#include "../../includes/minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = gc_add(shell, getcwd(NULL, 0));
	ft_putendl_fd(pwd, 1);
	return (0);
}
