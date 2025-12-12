/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:34:24 by tecker            #+#    #+#             */
/*   Updated: 2025/03/30 17:16:29 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

// copies characters from src to dest, but makes sure there is space for it
// returns length of copied content if space was there for all

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	i = 0;
	if (destsize > 0)
	{
		while (src[i] && i < (destsize - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
//     char dest1[1] = "";
//     char dest2[1] = "";

//     char *src = "hallo";
//     printf("%zu\n", ft_strlcpy(dest1, src, 1));
//     printf("%lu\n", strlcpy(dest2, src, 1));
//     printf("%s\n", dest1);
//     printf("%s\n", dest2);

// }