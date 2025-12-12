/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:13:37 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:13:38 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// utils -----
t_ast_node	*create_ast_node(t_ast_nodeType type, t_parser *p)
{
	t_ast_node	*node;

	node = gc_malloc(p->shell, sizeof(t_ast_node));
	node->type = type;
	ft_memset(&node->u_data, 0, sizeof(node->u_data));
	return (node);
}

void	advance_token(t_parser *p)
{
	if (p->current_token)
		p->current_token = p->current_token->next;
}

bool	check_token_type(t_parser *p, t_tokenType type)
{
	return (p->current_token && p->current_token->type == type);
}
// -----

// recursive descent parser
// parser assumes valid syntax (checked by validator)

// PRECEDENCE:
// - Redirects and arguments
// - Pipes
// - Logical OR / AND

void	parser(t_shell *shell)
{
	t_parser	p;

	p.shell = shell;
	p.current_token = shell->tokens.head;
	shell->ast = parse_logical(&p);
}
