/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 06:01:12 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/24 06:01:15 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pp(char **pp)
{
	int		i;

	i = 0;
	if (pp == NULL)
		return ;
	while (pp[i])
		free(pp[i++]);
	free(pp);
}

void	free_token(t_token **token)
{
	t_token	*ptr;

	ptr = (*token);
	if (!ptr)
		return ;
	while (ptr->next)
	{
		ptr = ptr->next;
		free(ptr->prev->str);
		free(ptr->prev);
	}
	if (ptr)
	{
		free(ptr->str);
		free(ptr);
	}
	*token = NULL;
}
	// free(*token);

void	free_here_doc(t_prompt *p)
{
	int	i;

	i = -1;
	while (++i < p->nbr_here_doc)
	{
		if (p->here_docs[i].delim)
			free (p->here_docs[i].delim);
		p->here_docs[i].delim = NULL;
		close(p->here_docs[i].pipefd[READEND]);
		close(p->here_docs[i].pipefd[WRITEEND]);
	}
	if (p->here_docs)
		free (p->here_docs);
	p->here_docs = NULL;
}

void	free_all(t_prompt *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->nbr_request)
	{
		if (p->requests)
		{
			j = -1;
			while (p->requests[i].tab && p->requests[i].tab[++j])
				free (p->requests[i].tab[j]);
			free (p->requests[i].tab);
			if (p->requests[i].token)
				free_token(&(p->requests[i].token));
			free (p->requests[i].str);
			free (p->requests[i].cmd);
		}
		i++;
	}
	free_here_doc(p);
	free (p->requests);
	free (p->clean);
}
