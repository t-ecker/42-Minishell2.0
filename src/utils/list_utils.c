#include "../../includes/minishell.h"

t_tokenList* create_tokenList(t_shell *shell)
{
    t_tokenList *list;
	
	list = malloc(sizeof(t_tokenList));
    if (!list)
		fatal_error(shell, MALLOC_ERROR);
    list->head = NULL;
    list->size = 0;
    return (list);
}

void add_token(t_tokenList *list, TokenType type, char *value, t_shell *shell)
{
    t_token *token;
	t_token *current;
	
	token = malloc(sizeof(t_token));
    if (!token)
		fatal_error(shell, MALLOC_ERROR);
    token->type = type;
    token->value = ft_strdup(value);
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
