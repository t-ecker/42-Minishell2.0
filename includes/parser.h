

#ifndef PARSER_H
# define PARSER_H

# include "./lexer.h"

typedef struct s_astNode t_astNode;

typedef struct s_parser
{
	t_shell *shell;
	t_tokenList	*tokens;
	t_token		*current_token;
}	t_parser;

typedef struct s_argList
{
	char				*value;
	struct s_argList	*next;
}	t_argList;

typedef enum s_redirectType
{
	REDIR_ERROR = -1,
	REDIR_INPUT,// <
	REDIR_OUTPUT,// >
	REDIR_APPEND,// >>
	REDIR_HEREDOC// <<
}	t_redirectType;

typedef struct s_redirectList
{
	t_redirectType	type;
	char			*target;
	struct s_redirectList	*next;
}	t_redirectList;

typedef struct s_commandNode
{
    t_argList *args;
    t_redirectList *redirects;
} t_commandNode;

typedef struct s_pipelineList
{
    t_astNode *command;
    struct s_pipelineList *next;
} t_pipelineList;

typedef struct s_pipelineNode
{
    t_pipelineList *commands;
} t_pipelineNode;

typedef enum s_binaryOpType
{
    BINOP_AND,
    BINOP_OR
} t_binaryOpType;

typedef struct s_binaryOpNode
{
    t_binaryOpType op_type;
    t_astNode *left;
    t_astNode *right;
} t_binaryOpNode;

typedef struct s_subshellNode
{
    t_astNode *child;
} t_subshellNode;

typedef enum t_astNodeType
{
    AST_COMMAND,
    AST_PIPELINE,
    AST_BINARY_OP,
	AST_SUBSHELL
} t_astNodeType;

typedef struct s_astNode
{
	t_astNodeType	type;
	union
	{
		t_commandNode command;
		t_pipelineNode pipeline;
		t_binaryOpNode binary_op;
		t_subshellNode subshell;
	}	u_data;
} t_astNode;

// union shares memory for all node type structs. size is largest member, but all other members could fit as well.
// Only one member is active, determined by ASTNode.type (need to be carefull).


# endif