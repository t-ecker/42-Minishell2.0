#ifndef EXPANDER_H
# define EXPANDER_H

# include <dirent.h>

typedef struct s_shell	t_shell;

typedef struct s_expand
{
	char	*res;
	bool	inside_single_quote;
	bool	inside_double_quote;
	size_t	capacity;
	t_shell	*shell;
}	t_expand;

typedef struct s_fileList
{
	char				*filename;
	struct s_fileList	*next;
}	t_fileList;

t_argList	*expander(char *str, t_shell *shell);
char		*expand_var(char *str, t_shell *shell);
void		init_expander(t_expand *e, t_shell *shell);
void		append_str(char *str, t_expand *e);
void		append_char(char c, t_expand *e);
t_argList	*expand_wildcard(t_argList *args, t_shell *shell);
bool		is_match(char *pattern, char *filename);
t_argList	*word_split(char *str, t_shell *shell);
void		remove_quotes_from_list(t_argList *args, t_shell *shell);

bool		found_quote(char c, bool *inside_double_quote,
				bool *inside_single_quote, int *i);
bool		has_unquoted_wildcard(char *word);
void		add_match(t_fileList **head, char *filename, t_shell *shell);
t_fileList	*create_filename_node(char *filename, t_shell *shell);
void		sort_matches(t_fileList **list);
t_argList	*file_to_arg_list(t_fileList *matches, t_shell *shell);

#endif