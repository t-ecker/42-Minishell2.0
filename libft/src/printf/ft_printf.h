/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:27:21 by tecker            #+#    #+#             */
/*   Updated: 2025/12/11 23:54:31 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../../libft.h"

int	ft_putnbr(int n);
int	ft_putpointer(void *ptr);
int	ft_putnbr_unsigned(unsigned int n);
int	ft_putstr(char *c);
int	ft_puthex(int n, char c);
int	ft_printf(const char *a, ...);
int	ft_putchar(char c);
int	check(int i, int b);

#endif