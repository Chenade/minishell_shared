/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:56:07 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/07 23:56:47 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ans;

	if (!s)
		return (0);
	i = 0;
	ans = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ans)
		return (0);
	while (s[i])
	{
		ans[i] = f(i, s[i]);
		i++;
	}
	ans[i] = 0;
	return (ans);
}
