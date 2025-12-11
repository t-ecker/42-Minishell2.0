#include "../../includes/minishell.h"

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
	int			max_len;
	char		*swap;

	current = *list;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strlen(current->filename) > ft_strlen(next->filename))
				max_len = ft_strlen(current->filename);
			else
				max_len = ft_strlen(next->filename);
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
