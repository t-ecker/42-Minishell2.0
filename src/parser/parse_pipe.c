# include "../../includes/minishell.h"

t_pipelineList *create_pipe_node(t_astNode *command, t_parser *p)
{
	t_pipelineList *node;
	
	node = gc_malloc(p->shell, sizeof(t_pipelineList));
	node->command = command;
	node->next = NULL;
	return (node);
}

void add_pipe_node(t_pipelineList **head, t_astNode *command, t_parser *p)
{
	t_pipelineList *node;
	t_pipelineList *current_node;
	
	node = create_pipe_node(command, p);
	if (*head == NULL)
		*head = node;
	else
	{
		current_node = *head;
		while(current_node->next)
			current_node = current_node->next;
		current_node->next = node;
	}
}

// first it parses left side of a pipe (cmd ())
// then if there is a pipe, it creates pipe node that stores all commands after another in a list

t_astNode *parse_pipe(t_parser *p)
{
	t_astNode *first_cmd;
	t_astNode *next_cmd;
	t_astNode *pipe_node;
	
	first_cmd = parse_subshell(p);
	// null check
	if (!check_token_type(p, TOKEN_PIPE))
		return (first_cmd);
	pipe_node = create_astNode(AST_PIPE, p);

	add_pipe_node(&pipe_node->u_data.pipeline.commands, first_cmd, p);
	while(check_token_type(p, TOKEN_PIPE))
	{
		advance_token(p);
		next_cmd = parse_subshell(p);
		// check cmd
		add_pipe_node(&pipe_node->u_data.pipeline.commands, next_cmd, p);
	}
	return(pipe_node);
}