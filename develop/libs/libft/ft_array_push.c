/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 06:10:32 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/24 06:10:34 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_array_push(char ***array, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	if (*array == NULL)
	{
		*array = (char **)malloc(sizeof(char *) * 2);
		(*array)[0] = ft_strdup(str);
		(*array)[1] = NULL;
		return (0);
	}
	while ((*array)[i] != NULL)
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*array)[i] != NULL)
	{
		tmp[i] = ft_strdup((*array)[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	ft_free_matrix(*array);
	*array = tmp;
	return (0);
}
