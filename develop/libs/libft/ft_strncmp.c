/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 00:00:53 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/08 00:01:12 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		ans;
	size_t	i;

	ans = 0;
	i = 0;
	while (i < n && !(ans))
	{
		ans = (unsigned char) s1[i] - (unsigned char) s2[i];
		if (s1[i] == 0 && s2[i] == 0)
			break ;
		i += 1;
	}
	return (ans);
}
