/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:54:49 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/07 23:54:57 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		ans;
	int		sign;

	i = 0;
	ans = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i += 1;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		sign = 44 - nptr[i];
		i += 1;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		ans *= 10;
		ans = ans + nptr[i] - 48;
		i += 1;
	}
	return (ans * sign);
}
