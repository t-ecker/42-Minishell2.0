#include "../../includes/minishell.h"

t_tokenList* create_tokenList(t_shell *shell)
{
    t_tokenList *list;
	
	list = gc_malloc(shell, sizeof(t_tokenList));
    list->head = NULL;
    list->size = 0;
    return (list);
}

void add_token(t_tokenList *list, TokenType type, char *value, t_shell *shell)
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
