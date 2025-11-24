# include "../../includes/minishell.h"


void free_shell(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		free_tokens(shell->tokens);
}

void free_tokens(t_tokenList *tokens)
{
    t_token *current;
    t_token *next;
	
	current = tokens->head;
    while (current)
	{
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    free(tokens);
}

// void free_env(idk)
