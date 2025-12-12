/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:13:19 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:13:20 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// checks if we have a group ()
// if so parse it from the very beginning
// if not, just parse a cmd

t_ast_node	*parse_group(t_parser *p)
{
	t_ast_node	*inner;
	t_ast_node	*group_node;

	if (check_token_type(p, TOKEN_LPAREN))
	{
		advance_token(p);
		inner = parse_logical(p);
		advance_token(p);
		group_node = create_ast_node(AST_GROUP, p);
		group_node->u_data.group.child = inner;
		return (group_node);
	}
	return (parse_cmd(p));
}
