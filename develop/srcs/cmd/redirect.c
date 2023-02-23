/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:12:05 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/21 09:12:06 by ykuo             ###   ########.fr       */
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

int	exit_fork(t_request *request, t_prompt *prompt, int status)
{
	if (prompt->nbr_request > 1 || !is_builtin(request->cmd))
	{
		free_all(prompt);
		free_pp(prompt->envp);
		clear_history();
	}
	exit (status);
}

int	redirection_heredoc(t_request *request, t_prompt *prompt, t_token *token)
{
	return (0);
}

int	redirect_fd(t_request *request, t_prompt *prompt, t_token *token)
{
	int	fd;

	if (token->next && token->next->type == 2)
	{
		fd = ft_open(token->type, token->next->str);
		if (fd < 0)
			exit_fork(request, prompt,
				print_redirect_error(token->type, token->next->str));
		else
		{
			if (token->type == 7 || token->type == 9)
				dupnclose(fd, STDOUT_FILENO);
			if (token->type == 6)
				dupnclose(fd, STDIN_FILENO);
		}
	}
	else
		exit_fork(request, prompt, print_error(SYNERR, "", token->str));
}

int	redirection(t_request *request, t_prompt *prompt)
{
	int		fd;	
	t_token	*token;

	token = request->token;
	while (token)
	{
		if (token->type == 7 || token->type == 9 || token->type == 6)
			redirect_fd(request, prompt, token);
		if (token->type == 8)
			redirection_heredoc(request, prompt, token);
		if (!token->next)
			break ;
		token = token->next;
	}
	return (0);
}
