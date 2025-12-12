/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:32:26 by tecker            #+#    #+#             */
/*   Updated: 2025/03/30 16:54:53 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

// checks if c is alpha or num

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || ((c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')));
}
// #include <stdio.h>
// #include <ctype.h>
// int main(void)
// {
//     char c = '=';
//     printf("%d\n", ft_isalnum(c));
//     printf("%d\n", isalnum(c));
//     return (0);
// }