/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 00:13:35 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/10 22:50:59 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dest_t;
	char	*src_t;

	i = 0;
	dest_t = (char *) dest;
	src_t = (char *) src;
	while (i < n)
	{
		dest_t[i] = src_t[i];
		i += 1;
	}
	return (dest_t);
}
