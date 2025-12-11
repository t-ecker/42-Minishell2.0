#include "../../includes/minishell.h"

t_gc_node	*gc_create_node(t_shell *shell, void *ptr)
{
	t_gc_node	*node;

	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		fatal_error(shell, MALLOC_ERROR);
	}
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}

void	*gc_malloc(t_shell *shell, size_t size)
{
	void		*ptr;
	t_gc_node	*node;

	ptr = malloc(size);
	if (!ptr)
		fatal_error(shell, MALLOC_ERROR);
	node = gc_create_node(shell, ptr);
	node->next = shell->gc.head;
	shell->gc.head = node;
	return (ptr);
}

void	*gc_add(t_shell *shell, void *ptr)
{
	t_gc_node	*node;

	if (!ptr)
		fatal_error(shell, MALLOC_ERROR);
	node = gc_create_node(shell, ptr);
	node->next = shell->gc.head;
	shell->gc.head = node;
	return (ptr);
}

void	*gc_realloc(t_shell *shell, void *ptr, size_t new_size,
			size_t bytes_to_cpy)
{
	void	*new_ptr;

	new_ptr = gc_malloc(shell, new_size);
	ft_memcpy(new_ptr, ptr, bytes_to_cpy);
	gc_free(shell, ptr);
	return (new_ptr);
}

void	gc_free(t_shell *shell, void *ptr)
{
	t_gc_node	*current;
	t_gc_node	*prev;

	if (!ptr)
		return ;
	current = shell->gc.head;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->gc.head = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_free_all(t_shell *shell)
{
	t_gc_node	*current;
	t_gc_node	*next;

	if (!shell->gc.head)
		return ;
	current = shell->gc.head;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	shell->gc.head = NULL;
}
