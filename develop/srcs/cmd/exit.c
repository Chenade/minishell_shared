/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 02:15:45 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/25 02:15:47 by ykuo             ###   ########.fr       */
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
	while (tmp->str[++i])
	{
		if (ft_isalpha(tmp->str[i]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(tmp->str, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required", STDERR_FILENO);
			return (2);
		}
	}
	if (tmp->str[i] == '\0')
		g_exit_status = ft_atoi(tmp->str);
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
	{
		ft_wait(prompt);
		g_exit_status = 0;
	}
	fprintf(stderr, "exit status: %d\n", g_exit_status);
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