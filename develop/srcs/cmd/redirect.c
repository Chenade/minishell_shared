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

int	error_message_fd(int type, char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if ((type == 7 || type == 9) && fd == -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if ((type == 6) && fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	if (folder)
		closedir(folder);
	close(fd);
	g_sig.exit_status = 1;
	return (g_sig.exit_status);
}

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
	else if (type == 8)
		fd = open(path, O_RDONLY, 0666);
	return (fd);
}

int	redirect_output(t_request *request)
{
	t_token	*token;

	token = request->token;
	while (token)
	{
		if (token->type == 7 || token->type == 9)
		{
			if (token->next && token->next->type == 2)
			{
				if (request->output_fd != 1)
					ft_close(request->output_fd);
				request->output_fd = ft_open(token->type, token->next->str);
				if (request->output_fd < 0)
					return (error_message_fd(token->type, token->next->str));
			}
			else
				return (print_error(SYNERR, "", token->str));
		}
		if (!token->next)
			break ;
		token = token->next;
	}
	return (0);
}

int	redirect_input2(t_request *request)
{
	t_token	*token;

	token = request->token;
	while (token)
	{
		if (!token->next)
			break ;
		token = token->next;
	}
	return (0);
}

int	redirect_input(t_request *request)
{
	t_token	*token;

	token = request->token;
	while (token)
	{
		if (token->type == 6)
		{
			if (token->next && token->next->type == 2)
			{
				if (request->input_fd != 0)
					close(request->input_fd);
				request->input_fd = ft_open(token->type, token->next->str);
				if (request->input_fd < 0)
					return (error_message_fd(token->type, token->next->str));
			}
			else
				return (print_error(SYNERR, "", token->str));
		}
		if (!token->next)
			break ;
		token = token->next;
	}
	return (0);
}


int	redirect_fd(t_request *request)
{
	redirect_output (request);
	return (0);
}
