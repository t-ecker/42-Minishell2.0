/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:32:46 by tecker            #+#    #+#             */
/*   Updated: 2025/03/30 16:57:37 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

// checks if c is a printable character including space

int	ft_isprint(int c)
{
	return ((c >= 32 && c <= 126));
}
// #include <stdio.h>
// #include <ctype.h>
// int main(void)
// {
//     char c = '1';
//     printf("%d\n", ft_isprint(c));
//     printf("%d\n", isprint(c));
//     return (0);
// }