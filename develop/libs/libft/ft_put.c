/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:00:48 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/10 19:01:37 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int *len)
{
	write (1, &c, 1);
	*len += 1;
}

void	ft_putstr(char *s, int *len)
{
	int	i;

	if (!(s))
		ft_putstr ("(null)", len);
	else
	{
		i = -1;
		while (s[++i])
			ft_putchar (s[i], len);
	}
}

void	ft_putnbr(int nbr, int *len)
{
	long int	n;

	n = (long) nbr;
	if (n < 0)
	{
		ft_putchar('-', len);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr(n / 10, len);
	ft_putchar((n % 10) + 48, len);
}
