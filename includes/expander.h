#ifndef EXPANDER_H
# define EXPANDER_H

#include <dirent.h>

typedef struct s_expand
{
	char *res;
	bool insideSingleQuote;
	bool insideDoubleQuote;
	size_t capacity;
	t_shell *shell;
} t_expand;

typedef struct s_fileList
{
	char *filename;
	struct s_fileList *next;
}	t_fileList;

void expander(char **str, t_shell *shell);
char *expand_var(char *str, t_shell *shell);
void init_expander(t_expand *e, t_shell *shell);
void append_str(char *str, t_expand *e);
void append_char(char c, t_expand *e);
char *expand_wildcard(char *str, t_shell *shell);
bool is_match(char *pattern, char *filename);



#endif