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
		if (pattern[i] == '\'' || pattern[i] == '"')
		{
			toggle_quote(pattern[i], &inside_double_quote, \
				&inside_single_quote);
			++i;
			continue ;
		}
		if (pattern[i] == '*' && !inside_double_quote && !inside_single_quote)
			return (found_wildcard(pattern, filename, i, j));
		else if (pattern[i] == filename[j])
		{
			++i;
			++j;
		}
		else
			return (false);
	}
	while (pattern[i] == '*')
		++i;
	return (!pattern[i] && !filename[j]);
}

t_fileList	*create_filename_node(char *filename, t_shell *shell)
{
	t_fileList	*node;

	node = gc_malloc(shell, sizeof(t_fileList));
	node->filename = gc_add(shell, ft_strdup(filename));
	node->next = NULL;
	return (node);
}

void	add_match(t_fileList **head, char *filename, t_shell *shell)
{
	t_fileList	*node;
	t_fileList	*current_node;

	node = create_filename_node(filename, shell);
	if (*head == NULL)
		*head = node;
	else
	{
		current_node = *head;
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = node;
	}
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

bool	has_unquoted_wildcard(char *word)
{
	int		pos;
	bool	inside_double_quote;
	bool	inside_single_quote;

	inside_double_quote = false;
	inside_single_quote = false;
	pos = 0;
	while (word[pos])
	{
		if (word[pos] == '\'' || word[pos] == '"')
			toggle_quote(word[pos], &inside_double_quote, &inside_single_quote);
		else if (word[pos] == '*' && !inside_single_quote
			&& !inside_double_quote)
			return (true);
		++pos;
	}
	return (false);
}

t_argList	*file_to_arg_list(t_fileList *matches, t_shell *shell)
{
	t_argList	*args;
	t_fileList	*current;

	args = NULL;
	current = matches;
	while (current)
	{
		add_arg_node(&args, current->filename, shell);
		current = current->next;
	}
	return (args);
}

void	sort_matches(t_fileList **list)
{
	t_fileList	*current;
	t_fileList	*next;
	int			len1;
	int			len2;
	int			max_len;
	char		*swap;

	current = *list;
	while (current)
	{
		next = current->next;
		while (next)
		{
			len1 = ft_strlen(current->filename);
			len2 = ft_strlen(next->filename);
			if (len1 > len2)
				max_len = len1;
			else
				max_len = len2;
			if (ft_strncmp(current->filename, next->filename, max_len) > 0)
			{
				swap = current->filename;
				current->filename = next->filename;
				next->filename = swap;
			}
			next = next->next;
		}
		current = current->next;
	}
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
