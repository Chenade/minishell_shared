/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:34:15 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/10 19:04:52 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_func(const char s, va_list lst, int *len)
{
	if (s == 'c')
		ft_putchar (va_arg (lst, int), len);
	else if (s == 's')
		ft_putstr (va_arg (lst, char *), len);
	else if (s == 'p')
		func_p (va_arg (lst, unsigned long), "0123456789abcdef", len);
	else if (s == 'd' || s == 'i')
		ft_putnbr (va_arg (lst, int), len);
	else if (s == 'u')
		func_u (va_arg (lst, unsigned int), len);
	else if (s == 'x')
		ft_puthex (va_arg (lst, unsigned int), "0123456789abcdef", len);
	else if (s == 'X')
		ft_puthex (va_arg (lst, unsigned int), "0123456789ABCDEF", len);
	else if (s == '%')
		ft_putchar (37, len);
}

int	ft_printf(const char *s, ...)
{
	int		len;
	int		i;
	int		is_break;
	va_list	lst;

	if (!(*s))
		return (0);
	va_start (lst, s);
	i = -1;
	len = 0;
	is_break = 1;
	while (s[++i] && is_break)
	{
		if (s[i] == '%')
		{
			if (!s[++i])
				is_break = 0;
			ft_printf_func (s[i], lst, &len);
		}
		else
			ft_putchar (s[i], &len);
	}
	va_end (lst);
	return (len);
}
