#include "../../includes/minishell.h"

const char* token_type_to_string(TokenType type)
{
    switch (type)
	{
        case TOKEN_WORD: return "WORD";
        case TOKEN_PIPE: return "PIPE";
        case TOKEN_OR: return "OR";
        case TOKEN_AND: return "AND";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_REDIRECT_IN: return "REDIRECT_IN";
        case TOKEN_REDIRECT_OUT: return "REDIRECT_OUT";
        case TOKEN_APPEND_OUT: return "APPEND_OUT";
        case TOKEN_HEREDOC: return "HEREDOC";
        case TOKEN_EOF: return "EOF";
        default: return "UNKNOWN";
    }
}

void print_tokens(t_tokenList *tokens)
{
    printf("Tokens (%zu):\n", (size_t)tokens->size);
    t_token *current = tokens->head;
    int i = 0;
    while (current)
	{
		if (current->type != TOKEN_EOF)
			printf("  [%d] %s: %s\n", i++, 
				token_type_to_string(current->type),
				current->value ? current->value : "nothing");
		else
			printf("  [%d] %s\n", i++, 
				token_type_to_string(current->type));
        current = current->next;
    }
}