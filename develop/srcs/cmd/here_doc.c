/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 05:53:01 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/24 05:53:03 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_delims(t_prompt *prompt)
{
	int		i;
	int		index;
	t_token	*token;

	i = -1;
	index = 0;
	while (++i < prompt->nbr_request)
	{
		token = prompt->requests[i].token;
		while (token)
		{
			if (token->type == HERE_DOC)
			{
				prompt->here_docs[index].delim = ft_strdup(token->next->str);
				pipe(prompt->here_docs[index].pipefd);
				index++;
				token = token->next;
			}
			token = token->next;
		}
	}
	return ;
}

static void	exit_here_doc(int sig)
{
	t_prompt	*prompt;
	int			i;

	prompt = starton();
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		g_exit_status = 130;
		free_all(prompt);
		free_pp(prompt->envp);
		exit(g_exit_status);
	}
}

static void	child_hd(t_prompt *prompt)
{
	char	*str;
	int		index;

	signal(SIGINT, &exit_here_doc);
	index = -1;
	while (++index < prompt->nbr_here_doc)
	{
		while (42)
		{
			str = readline(">");
			if (!str || !ft_strcmp(str, prompt->here_docs[index].delim))
				break ;
			ft_putendl_fd(str, prompt->here_docs[index].pipefd[1]);
			free(str);
		}
		close(prompt->here_docs[index].pipefd[WRITEEND]);
		close(prompt->here_docs[index].pipefd[READEND]);
	}
	free_all(prompt);
	free_pp(prompt->envp);
	clear_history();
	exit(1);
}

int	count_here_doc(t_prompt *prompt)
{
	int		i;
	int		nb;
	t_token	*token;

	i = -1;
	nb = 0;
	while (++i < prompt->nbr_request)
	{
		token = prompt->requests[i].token;
		while (token)
		{
			if (token->type == HERE_DOC)
				nb++;
			token = token->next;
		}
	}
	return (nb);
}

void	*here_doc(t_prompt *prompt)
{
	int		i;
	pid_t	pid;

	prompt->nbr_here_doc = count_here_doc(prompt);
	if (prompt->nbr_here_doc == 0)
		return (NULL);
	prompt->here_docs = ft_calloc(sizeof(t_here_doc), prompt->nbr_here_doc);
	if (!prompt->here_docs)
		return (NULL);
	ft_set_delims(prompt);
	pid = fork();
	i = -1;
	if (pid == 0)
		child_hd(prompt);
	else
		while (++i < prompt->nbr_here_doc)
			close(prompt->here_docs[i].pipefd[WRITEEND]);
	waitpid(pid, NULL, 0);
	return (NULL);
}
