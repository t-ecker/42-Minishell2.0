#include "../../includes/minishell.h"

long	ft_atol(char *str)
{
	long	sign;
	long	result;

	sign = 1;
	result = 0;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

bool	would_overflow(char *arg)
{
	int		i;
	int		sign;
	int		len;
	char	*relevant_part;

	i = 0;
	sign = 1;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		++i;
	}
	while (arg[i] == '0')
		++i;
	relevant_part = &arg[i];
	len = ft_strlen(relevant_part);
	if (len > 19)
		return (true);
	if (len < 19)
		return (false);
	if (sign == 1)
		return (ft_strncmp(relevant_part, "9223372036854775807", 19) > 0);
	return (ft_strncmp(relevant_part, "9223372036854775808", 19) > 0);
}

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
		++i;
	if (!arg[i])
		return (exit_error_numeric(arg), 2);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (exit_error_numeric(arg), 2);
		++i;
	}
	if (would_overflow(arg))
		return (exit_error_numeric(arg), 2);
	return ((unsigned char)ft_atol(arg));
}

int	ft_exit(char **args, t_shell *shell)
{
	if (args[1])
	{
		if (args[2])
		{
			ft_putendl_fd("exit", 1);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putendl_fd("too many arguments", 2);
			return (1);
		}
		else
			shell->exit_code = check_arg(args[1]);
	}
	else
		ft_putendl_fd("exit", 1);
	free_all(shell);
	exit(shell->exit_code);
}
