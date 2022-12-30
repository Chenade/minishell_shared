/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:52:49 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/07 23:52:53 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// specific change for fdf on line 36.
// original : ret[i++] = s2[j];

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2[0])
		return (s1);
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (0);
	while (s1 && s1[i])
		ret[i++] = s1[j++];
	j = 0;
	while (s2[j] && s2[j] != '\n')
		ret[i++] = s2[j++];
	if (s2[j] == '\n')
		ret[i++] = 32;
	ret[i] = 0;
	free(s1);
	return (ret);
}
