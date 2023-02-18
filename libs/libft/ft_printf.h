/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:28:05 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/10 19:03:31 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

void	ft_puthex(unsigned int n, char *base, int *len);
void	ft_puthex_pointer(unsigned long n, char *base, int *len);
void	func_p(unsigned long n, char *base, int *len);

void	func_u(unsigned int n, int *len);

void	ft_putnbr(int nbr, int *len);
void	ft_putstr(char *s, int *len);
void	ft_putchar(char c, int *len);

void	ft_printf_func(const char s, va_list lst, int *len);
int		ft_printf(const char *s, ...);

#endif