# include "../../includes/minishell.h"

void message(char *str)
{
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

long ft_atol(char *str)
{
    long sign = 1;
    long result = 0;

    if (*str == '+' || *str == '-')
        if (*str++ == '-')
            sign = -1;

    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}


int check_arg(char *arg)
{
	int i;

	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
		++i;
	if (!arg[i])
		return(message(arg), 255);
	while(arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return(message(arg), 2);
		++i;
	}
	return ((unsigned char)ft_atol(arg));
}

int ft_exit(char **args, t_shell *shell)
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
	free_all(shell);
	exit(shell->exit_code);
}
