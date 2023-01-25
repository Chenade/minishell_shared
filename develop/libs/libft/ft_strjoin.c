/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:52:49 by ykuo              #+#    #+#             */
/*   Updated: 2023/01/25 13:23:03 by jischoi          ###   ########.fr       */
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
	return (ret);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		len_s1;
// 	int		len_s2;
// 	char	*s3;
// 	int		i;

// 	if (s1 == NULL && s2 == NULL)
// 		return (NULL);
// 	i = 0;
// 	len_s1 = ft_strlen(s1);
// 	len_s2 = ft_strlen(s2);
// 	s3 = (char *)malloc(len_s1 + len_s2 + 1);
// 	if (s3 == NULL)
// 		return (NULL);
// 	while (i < len_s1 || i < len_s2)
// 	{
// 		if (i < len_s1)
// 			s3[i] = s1[i];
// 		if (i < len_s2)
// 			s3[i + len_s1] = s2[i];
// 		i++;
// 	}
// 	s3[len_s1 + len_s2] = '\0';
// 	return (s3);
// }