/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:12:10 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:12:11 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	found_wildcard(char *pattern, char *filename, int i, int j)
{
	++i;
	if (!pattern[i])
		return (true);
	while (filename[j])
	{
		if (is_match(pattern + i, filename + j))
			return (true);
		++j;
	}
	return (false);
}

bool	is_match(char *pattern, char *filename)
{
	int		i;
	int		j;
	bool	inside_double_quote;
	bool	inside_single_quote;

	i = 0;
	j = 0;
	inside_double_quote = false;
	inside_single_quote = false;
	while (pattern[i] && filename[j])
	{
		if (found_quote(pattern[i], &inside_double_quote, \
			&inside_single_quote, &i))
			continue ;
		if (pattern[i] == '*' && !inside_double_quote && !inside_single_quote)
			return (found_wildcard(pattern, filename, i, j));
		if (pattern[i] != filename[j])
			return (false);
		++i;
		++j;
	}
	while (pattern[i] == '*')
		++i;
	return (!pattern[i] && !filename[j]);
}

t_fileList	*find_wildcard_matches(char *pattern, t_shell *shell)
{
	DIR				*dir;
	t_fileList		*matches;
	struct dirent	*file;

	matches = NULL;
	dir = opendir(".");
	if (!dir)
		fatal_error(shell, OPENDIR_ERROR);
	file = readdir(dir);
	while (file)
	{
		if (file->d_name[0] == '.' && pattern[0] != '.')
		{
			file = readdir(dir);
			continue ;
		}
		if (is_match(pattern, file->d_name))
			add_match(&matches, file->d_name, shell);
		file = readdir(dir);
	}
	closedir(dir);
	return (matches);
}

t_argList	*process_word(char *word, t_shell *shell)
{
	t_fileList	*matches;

	if (!has_unquoted_wildcard(word))
		return (create_args_node(word, shell));
	matches = find_wildcard_matches(word, shell);
	if (!matches)
		return (create_args_node(word, shell));
	sort_matches(&matches);
	return (file_to_arg_list(matches, shell));
}

t_argList	*expand_wildcard(t_argList *args, t_shell *shell)
{
	t_argList	*current;
	t_argList	*last;
	t_argList	*res;
	t_argList	*expanded;

	res = NULL;
	last = NULL;
	current = args;
	while (current)
	{
		expanded = process_word(current->value, shell);
		if (!res)
		{
			res = expanded;
			last = res;
		}
		else
			last->next = expanded;
		while (last && last->next)
			last = last->next;
		current = current->next;
	}
	return (res);
}
