/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:10:36 by tecker            #+#    #+#             */
/*   Updated: 2025/12/15 15:09:42 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./lexer.h"

typedef struct s_astNode	t_ast_node;
typedef struct s_shell		t_shell;

typedef struct s_parser
{
	t_shell		*shell;
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
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redirectType;

typedef struct s_redirectList
{
	t_redirectType			type;
	char					*target;
	struct s_redirectList	*next;
}	t_redirectList;

typedef struct s_commandNode
{
	t_argList		*args;
	t_redirectList	*redirects;
}	t_commandNode;

typedef struct s_pipelineList
{
	t_ast_node				*command;
	struct s_pipelineList	*next;
}	t_pipelineList;

typedef struct s_pipelineNode
{
	t_pipelineList	*commands;
}	t_pipelineNode;

typedef enum s_logicalOpType
{
	LOG_OP_AND,
	LOG_OP_OR
}	t_logicalOpType;

typedef struct s_logicalOpNode
{
	t_logicalOpType	op_type;
	t_ast_node		*left;
	t_ast_node		*right;
}	t_logicalOpNode;

typedef struct s_groupNode
{
	t_ast_node	*child;
}	t_groupNode;

typedef enum t_ast_nodeType
{
	AST_COMMAND,
	AST_PIPE,
	AST_LOGICAL_OP,
	AST_GROUP
}	t_ast_nodeType;

typedef struct s_astNode
{
	t_ast_nodeType	type;
	union
	{
		t_commandNode		command;
		t_pipelineNode		pipeline;
		t_logicalOpNode		logical_op;
		t_groupNode			group;
	}	u_data;
}		t_ast_node;

// union shares memory for all node type structs. size is largest member,
	// but all other members could fit as well.
// Only one member is active, determined by ASTNode.type (need to be carefull).

// utils
bool		check_token_type(t_parser *p, t_tokenType type);
void		advance_token(t_parser *p);
t_ast_node	*create_ast_node(t_ast_nodeType type, t_parser *p);

t_ast_node	*parse_logical(t_parser *p);
t_ast_node	*parse_group(t_parser *p);
t_ast_node	*parse_pipe(t_parser *p);
t_ast_node	*parse_cmd(t_parser *p);
void		handle_redirection(t_redirectList **head, t_parser *p);
void		add_arg_node(t_argList **head, char *value, t_shell *shell);
t_argList	*create_args_node(char *value, t_shell *shell);

#endif