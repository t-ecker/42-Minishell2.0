/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:32:21 by tecker            #+#    #+#             */
/*   Updated: 2025/03/30 16:54:11 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

// allocates memory of size and fills it with \0

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
//     char *ptr;
//     char *ptr1;

//     ptr = ft_calloc(5, sizeof(char));
//     ptr = calloc(5, sizeof(char));

// }