/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 06:12:50 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/24 06:13:45 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(char **str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}
