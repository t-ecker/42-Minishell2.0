#include "../../includes/minishell.h"

void	cd_error(char *str, char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(str, 2);
}

void	update_vars(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	add_env_node(shell, ft_strdup("OLDPWD"), old_pwd);
	add_env_node(shell, ft_strdup("PWD"), new_pwd);
}

int	ft_cd(char **args, t_shell *shell)
{
	char	*path;
	char	*old_pwd;

	if (args[2])
		return (cd_error("too many arguments", NULL), 1);
	else if (!args[1])
	{
		path = get_env_var("HOME", shell);
		if (!path)
			return (cd_error("HOME not set", NULL), 1);
	}
	else if (ft_strlen(args[1]) == 1
		&& ft_strncmp(args[1], "-", ft_strlen(args[1])) == 0)
	{
		path = get_env_var("OLDPWD", shell);
		if (!path)
			return (cd_error("OLDPWD not set", NULL), 1);
	}
	else
		path = args[1];
	old_pwd = getcwd(NULL, 0);
	if (chdir(path))
		return (free(old_pwd), cd_error(strerror(errno), path), 1);
	return (update_vars(shell, old_pwd), 0);
}
