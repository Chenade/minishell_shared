/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 00:28:24 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/07 23:51:02 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	s;
	size_t	len_src;
	size_t	len_dest;

	s = 0;
	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (size <= len_dest)
		return (len_src + size);
	while (len_dest + s < size - 1 && src[s])
	{
		dest[len_dest + s] = src[s];
		s++;
	}
	dest[len_dest + s] = 0;
	return (len_src + len_dest);
}
