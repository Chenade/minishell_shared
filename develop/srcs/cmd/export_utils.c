/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 04:29:21 by jischoi           #+#    #+#             */
/*   Updated: 2023/03/02 04:29:22 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_norm_char(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i])
			&& str[i] != '=' && str[i] != '_' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}