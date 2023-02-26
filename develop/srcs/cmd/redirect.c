/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:57:16 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/26 00:29:11 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(int type, char *path)
{
	int	fd;

	fd = 0;
	if (type == 7)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (type == 9)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (type == 6)
		fd = open(path, O_RDONLY, 0666);
	return (fd);
}

int	exit_fork(t_request *request, t_prompt *prompt, int fd_stdout, int status)
{
	dupnclose (fd_stdout, STDOUT_FILENO);
	if (!(prompt->nbr_request == 1 || !is_builtin(request->cmd)))
	{
		fprintf(stderr, "sdfsdfdfs\n");
		free_all(prompt);
		free_pp(prompt->envp);
		clear_history();
		exit (status);
	}
	return (status);
}

int	redirect_heredoc(t_request *request, t_prompt *prompt,
	t_token *token, int sfd)
{
	int		i;
	int		fd;

	if (token->next && (token->next->type == 11 || token->next->type == 0))
	{
		i = -1;
		while (++i < prompt->nbr_here_doc)
		{
			if (ft_strcmp(prompt->here_docs[i].delim, token->next->str) == 0)
			{
				dupnclose(prompt->here_docs[i].pipefd[READEND], STDIN_FILENO);
				return (0);
			}
		}
	}
	else
		return (exit_fork(request, prompt, sfd,
				print_error(ABRT, "", token->str)));
	return (0);
}

int	redirect_fd(t_request *request, t_prompt *prompt, t_token *token, int sfd)
{
	int	fd;

	if (token->next && token->next->type == 11)
	{
		fd = ft_open(token->type, token->next->str);
		if (fd < 0)
			return (exit_fork(request, prompt, fd,
					print_redirect_error(token->type, token->next->str)));
		else
		{
			if (token->type == 7 || token->type == 9)
				dupnclose(fd, STDOUT_FILENO);
			if (token->type == 6)
				dupnclose(fd, STDIN_FILENO);
			return (0);
		}
	}
	else
		return (exit_fork(request, prompt, sfd,
				print_error(ABRT, "", token->str)));
}

int	redirection(t_request *request, t_prompt *prompt, int fd_stdout)
{
	int			fd;	
	t_token		*token;
	t_request	*tmp;

	tmp = request;
	token = tmp->token;
	while (token)
	{
		if (token->type == 7 || token->type == 9 || token->type == 6)
			if (redirect_fd(tmp, prompt, token, fd_stdout))
				return (1);
		if (token->type == 8)
			if (redirect_heredoc(tmp, prompt, token, fd_stdout))
				return (1);
		if (!token->next)
			break ;
		token = token->next;
	}
	return (0);
}
