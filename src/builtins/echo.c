#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (args[++i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] && args[i][j] == 'n')
			++j;
		if (j != 1 && !args[i][j])
			++flag;
		else
			break ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[++i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
