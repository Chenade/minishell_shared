/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 01:08:37 by ykuo              #+#    #+#             */
/*   Updated: 2022/05/08 01:09:04 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ans;

	ans = (t_list *) malloc (sizeof(t_list));
	if (!ans)
		return (0);
	ans->content = content;
	ans->next = NULL;
	return (ans);
}
