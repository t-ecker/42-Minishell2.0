# include "../../includes/minishell.h"

t_astNode *create_astNode(t_astNodeType type, t_parser *p)
{
	t_astNode *node;
	
	node = malloc(sizeof(t_astNode));
	if (!node)
		fatal_error(p->shell, MALLOC_ERROR);
	node->type = type;
	ft_memset(&node->u_data, 0, sizeof(node->u_data));
	return (node);
}

t_argList *create_args_node(char *value, t_parser *p)
{
	t_argList *node;
	
	node = malloc(sizeof(t_argList));
	if (!node)
		fatal_error(p->shell, MALLOC_ERROR);
	node->value = ft_strdup(value);
	if (!node->value)
		fatal_error(p->shell, MALLOC_ERROR);
	node->next = NULL;
	return (node);
}

void add_arg_node(t_argList **head, char *value, t_parser *p)
{
	t_argList *node;
	t_argList *current_node;
	
	node = create_args_node(value, p);
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

t_redirectList *create_redir_node(t_redirectType type, char *target, t_parser *p)
{
	t_redirectList *node;
	
	node = malloc(sizeof(t_redirectList));
	if (!node)
		fatal_error(p->shell, MALLOC_ERROR);
	node->type = type;
	node->target = ft_strdup(target);
	if (!node->target)
		fatal_error(p->shell, MALLOC_ERROR);
	node->next = NULL;
	return (node);
}

void add_arg_node(t_redirectList **head, t_redirectType type, char *target, t_parser *p)
{
	t_redirectList *node;
	t_redirectList *current_node;
	
	node = create_redir_node(type, target, p);
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

t_pipelineNode *create_pipe_node(t_astNode *command, t_parser *p)
{
	t_pipelineList *node;
	
	node = malloc(sizeof(t_pipelineList));
	if (!node)
		fatal_error(p->shell, MALLOC_ERROR);
	node->command = command;
	node->next = NULL;
	return (node);
}

void add_arg_node(t_pipelineList **head, t_astNode *command, t_parser *p)
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



int parser(t_shell *shell)
{

}