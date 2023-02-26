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

static int	ft_set_delims(t_prompt *prompt)
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
			if (token->type == HERE_DOC && token->next)
			{
				prompt->here_docs[index].delim = ft_strdup(token->next->str);
				pipe(prompt->here_docs[index].pipefd);
				index++;
				token = token->next;
			}
			token = token->next;
		}
	}
	return (index);
}

int	end_here_doc(char *str, t_prompt *prompt, int index)
{
	g_exit_status = 0;
	if (!str || !ft_strcmp(str, prompt->here_docs[index].delim))
	{
		if (!str)
		{
			ft_putstr_fd("minishell: warning: here-document at line 72", 2);
			ft_putstr_fd("delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(prompt->here_docs[index].delim, 2);
			ft_putstr_fd("')\n", 2);
		}
		return (1);
	}
	return (0);
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
			if (end_here_doc(str, prompt, index))
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
	exit(0);
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

int	here_doc(t_prompt *prompt)
{
	int		i;
	pid_t	pid;
	int		status;

	prompt->nbr_here_doc = count_here_doc(prompt);
	if (prompt->nbr_here_doc == 0)
		return (g_exit_status);
	prompt->here_docs = ft_calloc(sizeof(t_here_doc), prompt->nbr_here_doc);
	if (!prompt->here_docs)
		return (g_exit_status);
	if (!ft_set_delims(prompt))
		return (g_exit_status);
	pid = fork();
	i = -1;
	if (pid == 0)
		child_hd(prompt);
	else
		while (++i < prompt->nbr_here_doc)
			close(prompt->here_docs[i].pipefd[WRITEEND]);
	status = waitpid(pid, NULL, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	fprintf(stderr, "exit status: %d\n", g_exit_status);
	return (g_exit_status);
}
