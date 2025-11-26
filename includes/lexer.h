#ifndef LEXER_H
# define LEXER_H

typedef enum s_tokenType
{
	TOKEN_WORD,
    TOKEN_PIPE,        
    TOKEN_OR,          
    TOKEN_AND,         
    TOKEN_LPAREN,      
    TOKEN_RPAREN,      
    TOKEN_REDIRECT_IN, 
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND_OUT,  
    TOKEN_HEREDOC,     
    TOKEN_EOF
} t_tokenType;

typedef struct s_token
{
	t_tokenType type;
	char *value;
	struct s_token *next;
}	t_token;

typedef struct s_tokenList
{
	t_token *head;
	int size;
} t_tokenList;

# endif