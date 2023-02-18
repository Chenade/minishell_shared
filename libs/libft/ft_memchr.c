/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:49:32 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/08 21:17:19 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*str;

	i = -1;
	str = (unsigned char *) s;
	while ((size_t)++i < n)
	{
		if (str[i] == (unsigned char) c)
			return ((void *) s + i);
	}
	return (NULL);
}
