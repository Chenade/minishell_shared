/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:00:52 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/07 23:53:50 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int n)
{
	int	len;

	len = 0;
	while (n >= 1 || n <= -1)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*ans;

	len = ft_len(n);
	sign = 1;
	if (n <= 0)
	{
		sign = -1;
		len++;
	}
	ans = malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (0);
	ans[0] = 45;
	if (n == 0)
		ans[0] = 48;
	ans[len] = 0;
	while (--len >= 0 && (n >= 1 || n <= -1))
	{
		ans[len] = n % 10 * sign + 48;
		n /= 10;
	}
	return (ans);
}
