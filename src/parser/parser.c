# include "../../includes/minishell.h"

t_astNode *create_astNode(t_astNodeType type, t_parser *p)
{
	t_astNode *node;
	
	node = gc_malloc(p->shell, sizeof(t_astNode));
	node->type = type;
	ft_memset(&node->u_data, 0, sizeof(node->u_data));
	return (node);
}

t_argList *create_args_node(char *value, t_parser *p)
{
	t_argList *node;
	
	node = gc_malloc(p->shell, sizeof(t_argList));
	node->value = gc_add(p->shell, ft_strdup(value));
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
	
	node = gc_malloc(p->shell, sizeof(t_redirectList));
	node->type = type;
	node->target = gc_add(p->shell, ft_strdup(target));
	node->next = NULL;
	return (node);
}

void add_redir_node(t_redirectList **head, t_redirectType type, char *target, t_parser *p)
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



// int parser(t_shell *shell)
// {

// }