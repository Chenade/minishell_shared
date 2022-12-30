/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:52:23 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/07 23:52:35 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcnt(const char *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			cnt++;
		while (*s && *s != c)
			s++;
	}
	return (cnt);
}

size_t	ft_wordlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	wc;
	char	**tab;

	wc = ft_wordcnt(s, c);
	tab = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		while (*s == c)
			s++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_wordlen(s, c) + 1));
		if (!tab[i])
			return (NULL);
		j = 0;
		while (*s && *s != c)
			tab[i][j++] = *s++;
		tab[i++][j] = '\0';
	}
	tab[i] = NULL;
	return (tab);
}
