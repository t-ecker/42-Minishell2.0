/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:32:16 by tecker            #+#    #+#             */
/*   Updated: 2025/03/30 16:52:53 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

// writes len amount of \0 bytes to str

void	*ft_bzero(void *str, size_t len)
{
	size_t	i;
	char	*s;

	s = (char *)str;
	i = 0;
	while (i < len)
	{
		s[i] = '\0';
		i++;
	}
	return (str);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
//     char str1[30];
//     char str2[30];

//     ft_bzero(str1, 3);
//     printf("%s\n", str1);

//     bzero(str2, 3);
//     printf("%s\n", str2);
//     return (0);
// }