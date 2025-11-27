# include "../../includes/minishell.h"


// hardcoded version for now!
char *get_env_var(char *var_name, t_shell *shell)
{
	if (ft_strncmp(var_name, "HOME", ft_strlen(var_name)) == 0)
		return "/home/user";
	if (ft_strncmp(var_name, "USER", ft_strlen(var_name)) == 0)
		return "testuser";
	if (ft_strncmp(var_name, "PATH", ft_strlen(var_name)) == 0)
		return "/usr/bin:/bin";
	
	return NULL;
}
