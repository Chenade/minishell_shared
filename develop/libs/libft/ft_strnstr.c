/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:03:37 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/09 12:03:39 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	int		i;
	int		j;
	char	*str;
	char	*to_find;

	str = (char *) big;
	to_find = (char *) little;
	if (!(*(to_find)))
		return (str);
	i = 0;
	while (str[i] && (size_t) i < n)
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j] && (size_t)(i + j) < n)
			j += 1;
		if (to_find[j] == '\0')
			return (str + i);
		i += 1;
	}
	return (NULL);
}
