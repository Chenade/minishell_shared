/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 05:58:12 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/24 05:58:14 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 1;
	tmp = token;
	while (tmp->str)
	{
		printf("		%d ) STR : %15s  TYPE : %d  \n",
			i++, tmp->str, tmp->type);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
}

int	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
