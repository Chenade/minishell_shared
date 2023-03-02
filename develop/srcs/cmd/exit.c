/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 02:15:45 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/26 06:09:58 by jischoi          ###   ########.fr       */
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
		if (i + 1 < prompt->nbr_request)
			signal(SIGINT, SIG_IGN);
		else if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 2);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

int	get_exit_status(t_token *tmp)
{
	int		i;
	int		fd;
	int		ed;
	t_token	*tmp2;

	i = -1;
	tmp2 = tmp;
	fd = dup(STDOUT_FILENO);
	ed = dup(STDERR_FILENO);
	dupnclose(STDERR_FILENO, STDOUT_FILENO);
	while (tmp->str[++i])
		if (ft_isalpha(tmp->str[i]))
			return (printf("minishell: exit: %s: numeric argument equired\n",
					tmp->str), dupnclose(fd, STDOUT_FILENO), 2);
	if (i == 0)
		return (printf("minishell: exit: %s: numeric argument equired\n",
				tmp->str), dupnclose(fd, STDOUT_FILENO), 2);
	if (tmp2->next)
		return (dupnclose(ed, STDERR_FILENO), dupnclose(fd, STDOUT_FILENO), -1);
	g_exit_status = ft_atoi(tmp2->str);
	while (g_exit_status < 0)
		g_exit_status += 256;
	return (dupnclose(ed, STDERR_FILENO),
		dupnclose(fd, STDOUT_FILENO), g_exit_status);
}

int	exit_minishell(t_request *request, t_prompt *prompt, int fd_stdout)
{
	int		status;

	status = 0;
	if (request->token->next)
	{
		status = get_exit_status(request->token->next);
		if (status < 0)
			print_error(TM_ARGS, "exit", NULL);
	}
	else
		ft_wait(prompt);
	g_exit_status = status;
	if (status >= 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		free_all(prompt);
		free_pp(prompt->envp);
		clear_history();
		ft_close(fd_stdout);
		exit(g_exit_status);
	}
	else
		status = 1;
	return (status);
}

void	exit_here_doc(int sig)
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
