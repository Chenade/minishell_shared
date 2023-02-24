/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 06:03:06 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/24 06:03:09 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_str(char *str)
{
	while (*str)
	{
		*str = *(str + 1);
		str++;
	}
}

int	is_sep(char s)
{
	if (s == - '<' || s == - '>' || s == - '|' || s == - ' ' || s == - 'e')
		return (1);
	return (0);
}

int	is_quot(char s)
{
	if (s == '\'' || s == '\"')
		return (1);
	return (0);
}

int	ft_strchr_int(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

int	token_countcmd(t_token *token)
{
	int	ans;

	ans = 0;
	while (token)
	{
		if (token->type == 1)
			ans += 1;
		token = token->next;
	}
	return (ans);
}
