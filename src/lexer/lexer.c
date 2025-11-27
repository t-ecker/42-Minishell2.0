#include "../../includes/minishell.h"

void add_token(t_tokenList *list, t_tokenType type, char *value, t_shell *shell)
{
    t_token *token;
	t_token *current;
	
	token = gc_malloc(shell, sizeof(t_token));
    token->type = type;
    token->value = gc_add(shell, ft_strdup(value));
    token->next = NULL;
    
    if (list->head == NULL)
        list->head = token;
    else
	{
        current = list->head;
        while (current->next != NULL)
            current = current->next;
        current->next = token;
    }
    list->size++;
}

int check_double_char_operators(char *str, int *pos, t_tokenList *list, t_shell *shell)
{
	char a;
	char b;

	if (!str[*pos + 1])
		return 0;
	a = str[*pos];
	b = str[*pos + 1];

	if (a == '|' && b == a)
		add_token(list, TOKEN_OR, "||", shell);
	else if (a == '&' && b == a)
		add_token(list, TOKEN_AND, "&&", shell);
	else if (a == '<' && b == a)
		add_token(list, TOKEN_HEREDOC, "<<", shell);
	else if (a == '>' && b == a)
		add_token(list, TOKEN_APPEND_OUT, ">>", shell);
	else
		return (0);
	*pos += 2;
	return (1);
}

int check_single_char_operators(char *str, int *pos, t_tokenList *list, t_shell *shell)
{
	if (str[*pos] == '|')
		add_token(list, TOKEN_PIPE, "|", shell);
	else if (str[*pos] == '<')
		add_token(list, TOKEN_REDIRECT_IN, "<", shell);
	else if (str[*pos] == '>')
		add_token(list, TOKEN_REDIRECT_OUT, ">", shell);
	else if (str[*pos] == '(')
		add_token(list, TOKEN_LPAREN, "(", shell);
	else if (str[*pos] == ')')
		add_token(list, TOKEN_RPAREN, ")", shell);
	else
		return (0);
	(*pos)++;
	return (1);
}

void check_word(char *str, int *pos, t_tokenList *list, t_shell *shell)
{
	int end;
	char *value;

	end = *pos;
	while(str[end] && !is_special_char(str[end]) && !ft_isspace(str[end]))
	{
		if (str[end] == '\'' || str[end] == '"')
		{
			skip_quotes(str, &end);
			continue;
		}
		end++;
	}
	value = gc_add(shell, ft_substr(str, *pos, end - *pos));
	add_token(list, TOKEN_WORD, value, shell);
	*pos = end;
}

void lexer(t_shell *shell)
{
	int pos;
	char *str;
	t_tokenList tokens;

    tokens.head = NULL;
    tokens.size = 0;
	
	pos = 0;
	str = shell->input;
	while (str[pos])
	{
		skip_spaces(str, &pos);
		if (check_double_char_operators(str, &pos, &tokens, shell)
			|| check_single_char_operators(str, &pos, &tokens, shell))
			continue;
		check_word(str, &pos, &tokens, shell);
	}
	add_token(&tokens, TOKEN_EOF, "", shell);
	shell->tokens = tokens;
}
