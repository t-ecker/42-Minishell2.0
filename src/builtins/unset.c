#include "../../includes/minishell.h"

int	ft_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		delete_env_var(args[i], shell);
		++i;
	}
	return (0);
}
