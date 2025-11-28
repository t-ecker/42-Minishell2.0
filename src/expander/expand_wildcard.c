# include "../../includes/minishell.h"

bool found_wildcard(char *pattern, char *filename, int i, int j)
{
	++i;
	if (!pattern[i])
		return (true);
	while(filename[j])
	{
		if (is_match(pattern + i, filename + j))
			return (true);
		++j;
	}
	return (false);
}

bool is_match(char *pattern, char *filename)
{
	int i;
	int j;
	bool insideDoubleQuote;
	bool insideSingleQuote;
	
	i = 0;
	j = 0;
	insideDoubleQuote = false;
	insideSingleQuote = false;
	while(pattern[i] && filename[j])
	{
		if (pattern[i] == '\'' || pattern[i] == '"')
		{
			toggle_quote(pattern[i], &insideDoubleQuote, &insideSingleQuote);
			++i;
			continue;
		}
		if (pattern[i] == '*' && !insideDoubleQuote && !insideSingleQuote)
			return (found_wildcard(pattern, filename, i, j));
		else if (pattern[i] == filename[j])
		{
			++i;
			++j;
		}
		else
			return (false);
	}
	while(pattern[i] == '*')
		++i;
	return (!pattern[i] && !filename[j]);
}

t_fileList *create_fileName_node(char *filename, t_shell *shell)
{
	t_fileList *node;
	
	node = gc_malloc(shell, sizeof(t_fileList));
	node->filename = gc_add(shell, ft_strdup(filename));
	node->next = NULL;
	return (node);
}

void add_match(t_fileList **head, char *filename, t_shell *shell)
{
	t_fileList *node;
	t_fileList *current_node;
	
	node = create_fileName_node(filename, shell);
	if (*head == NULL)
		*head = node;
	else
	{
		current_node = *head;
		while(current_node->next)
			current_node = current_node->next;
		current_node->next = node;
	}
}

t_fileList *find_wildcard_matches(char *pattern, t_shell *shell)
{
	DIR *dir;
	t_fileList *matches;
	struct dirent *file;

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
			continue;
		}
		if (is_match(pattern, file->d_name))
			add_match(&matches, file->d_name, shell);			
		file = readdir(dir);
	}
	closedir(dir);
	return (matches);
}

void process_word(t_expand word, bool has_wildcard, t_expand *e)
{
	t_fileList *file_matches;
	t_fileList *current;

	if (has_wildcard)
	{
		file_matches = find_wildcard_matches(word.res, e->shell);
		if (file_matches)
		{
			current = file_matches;
			while (current)
			{
				append_str(current->filename, e);
				if (current->next)
					append_char(' ', e);
				current = current->next;
			}
		}
		else
			append_str(word.res, e);
	}
	else
		append_str(word.res, e);
}

void handle_word(char *str, int *pos, t_expand *e)
{
	t_expand word;
	bool has_wildcard;

	has_wildcard = false;
	init_expander(&word, e->shell);
	while(str[*pos] && !ft_isspace(str[*pos]))
	{
		if (str[*pos] == '\'' || str[*pos] == '"')
		{
			toggle_quote(str[*pos], &word.insideDoubleQuote, &word.insideSingleQuote);
			append_char(str[*pos], &word);
		}
		else if (str[*pos] == '*' && !word.insideSingleQuote && !word.insideDoubleQuote)
		{
			has_wildcard = true;
			append_char(str[*pos], &word);
		}
		else
			append_char(str[*pos], &word);
		++(*pos);
	}
	process_word(word, has_wildcard, e);
}

char *expand_wildcard(char *str, t_shell *shell)
{
	int pos;
	t_expand e;

	pos = 0;
	init_expander(&e, shell);
	while (str[pos])
	{
		if (ft_isspace(str[pos]))
		{
			append_char(str[pos], &e);
			++pos;
			continue;
		}
		handle_word(str, &pos, &e);
	}
	return (e.res);
}