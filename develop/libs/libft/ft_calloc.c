/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:45:32 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/07 23:45:53 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ans;

	ans = malloc (nmemb * size);
	if (!ans)
		return (0);
	ft_bzero((void *)ans, (nmemb * size));
	return ((void *)ans);
}
