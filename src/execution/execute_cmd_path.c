/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:11:22 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:11:23 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_in_path(char *cmd, t_shell *shell)
{
	char	*path;
	char	**paths;
	char	*full_path;
	int		i;

	path = get_env_var("PATH", shell);
	if (!path)
		return (NULL);
	paths = gc_add(shell, ft_split(path, ':'));
	i = 0;
	while (paths[i])
		gc_add(shell, paths[i++]);
	i = 0;
	while (paths[i])
	{
		full_path = gc_add(shell, ft_strjoin(paths[i], "/"));
		full_path = gc_add(shell, ft_strjoin(full_path, cmd));
		if (access(full_path, X_OK) == 0)
			return (full_path);
		++i;
	}
	return (NULL);
}

int	validate_path(char *path, char *cmd, bool is_absolute)
{
	struct stat	st;

	if (!path || stat(path, &st) < 0)
	{
		if (is_absolute)
			return (execution_error(NO_SUCH_FILE_ERROR, cmd), 127);
		return (execution_error(CMD_NOT_FOUND_ERROR, cmd), 127);
	}
	if (S_ISDIR(st.st_mode))
		return (execution_error(IS_DIR_ERROR, path), 126);
	if (access(path, X_OK) < 0)
		return (execution_error(PERMISSION_ERROR, path), 126);
	return (0);
}

int	get_cmd_path(char *cmd, t_shell *shell, char **path)
{
	bool	is_absolute;

	is_absolute = (ft_strchr(cmd, '/') != NULL);
	if (is_absolute)
		*path = cmd;
	else
		*path = search_in_path(cmd, shell);
	return (validate_path(*path, cmd, is_absolute));
}
