/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbageCollector.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:10:24 by tecker            #+#    #+#             */
/*   Updated: 2025/12/12 12:10:25 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGECOLLECTOR_H
# define GARBAGECOLLECTOR_H

# include <stdlib.h>

typedef struct s_shell	t_shell;

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*head;
}	t_gc;

void	gc_init(t_shell *shell);
void	*gc_malloc(t_shell *shell, size_t size);
void	*gc_add(t_shell *shell, void *ptr);
void	*gc_realloc(t_shell *shell, void *ptr, size_t new_size,
			size_t bytes_to_cpy);
void	gc_free(t_shell *shell, void *ptr);
void	gc_free_all(t_shell *shell);
void	gc_destroy(t_shell *shell);

#endif