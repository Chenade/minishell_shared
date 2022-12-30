/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 00:05:39 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/09 12:01:25 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *s2)
{
	size_t	s;
	size_t	len;
	char	*dst;

	if (!s1 || !s2)
		return (0);
	s = 0;
	len = ft_strlen(s1);
	while (s < len && ft_strchr(s2, s1[s]))
		s++;
	while (s < len && ft_strchr(s2, s1[len]))
		len -= 1;
	if (len == 0)
		dst = ft_substr(s1, 0, 0);
	else
		dst = ft_substr(s1, s, len - s + 1);
	if (!dst)
		return (0);
	return (dst);
}
