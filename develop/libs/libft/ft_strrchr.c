/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:48:49 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/07 23:49:09 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ans;

	i = -1;
	ans = NULL;
	while (s[++i])
	{
		if (s[i] == (unsigned char)c)
			ans = ((char *) s + i);
	}
	if (s[i] == (unsigned char)c)
		return ((char *) s + i);
	return (ans);
}
