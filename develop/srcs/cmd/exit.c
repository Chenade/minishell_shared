/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:15:56 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/24 16:46:35 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_prompt *prompt)
{
	int	status;
	int	i;

	i = -1;
	status = 0;
	while (++i < prompt->nbr_request)
	{
		waitpid(prompt->requests[i].pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

int	get_exit_status(t_token *tmp)
{
	int	i;

	i = -1;
	while (tmp->str[++i] && g_exit_status != 255)
	{
		if (!ft_isdigit(tmp->str[i]))
			g_exit_status = 255;
	}
	if (tmp->str[i] == '\0')
	{
		g_exit_status = ft_atoi(tmp->str);
		if (g_exit_status < 0 || g_exit_status > 255)
			g_exit_status = 255;
	}
	return (g_exit_status);
}

int	exit_minishell(t_request *request, t_prompt *prompt, int fd_stdout)
{
	int		status;
	t_token	*tmp;

	tmp = request->token->next;
	status = 0;
	if (tmp)
		g_exit_status = get_exit_status(tmp);
	else
		ft_wait(prompt);
	free_all(prompt);
	free_pp(prompt->envp);
	clear_history();
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_close(fd_stdout);
	exit(g_exit_status);
}

// int	exit_minishell(t_request *request, t_prompt *prompt, int fd_stdout)
// {
// 	int	status;

// 	status = 0;
// 	ft_wait(prompt);
// 	free_all(prompt);
// 	free_pp(prompt->envp);
// 	clear_history();
// 	ft_putstr_fd("exit\n", STDERR_FILENO);
// 	ft_close(fd_stdout);
// 	g_exit_status = 0;
// 	exit(g_exit_status);
// }