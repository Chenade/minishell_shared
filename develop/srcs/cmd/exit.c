/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 02:15:45 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/28 21:42:20 by jischoi          ###   ########.fr       */
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
	// t_token	*tmp2;

	// i = -1;
	// tmp2 = tmp;
	fd = dup(STDOUT_FILENO);
	ed = dup(STDERR_FILENO);
	dupnclose(STDERR_FILENO, STDOUT_FILENO);
	i = 0;
	while (tmp->str[i] && tmp->str[i] == ' ')
		i++;
	i -= 1;
	// while (tmp)
	// {
		while (tmp->type == 0 || tmp->str[++i])
			if (tmp->type == 0 || ft_isalpha(tmp->str[i]) || tmp->str[i] == ' ')
				return (printf("minishell: exit: %s: numeric argument "\
				"required\n", tmp->str), dupnclose(fd, STDOUT_FILENO), 2);
		// tmp = tmp->next;
	// }
	// if (tmp2->next)
	if (tmp->next)
		return (dupnclose(ed, STDERR_FILENO), dupnclose(fd, STDOUT_FILENO), -1);
	// g_exit_status = ft_atoi(tmp2->str);
	g_exit_status = ft_atoi(tmp->str);
	while (g_exit_status < 0)
		g_exit_status += 256;
	return (dupnclose(ed, STDERR_FILENO),
		dupnclose(fd, STDOUT_FILENO), g_exit_status);
}

int	if_exit(t_request *request, t_prompt *prompt, t_token *tmp)
{
	int	status;

	if (tmp)
	{
		status = get_exit_status(tmp);
		if (status < 0)
			print_error(TM_ARGS, "exit", NULL);
		g_exit_status = status;
	}
	else
	{
		ft_wait(prompt);
		g_exit_status = 0;
	}
	return (g_exit_status);
}

int	exit_minishell(t_request *request, t_prompt *prompt, int fd_stdout)
{
	int		status;
	t_token	*tmp;

	tmp = request->token->next;
	status = if_exit(request, prompt, tmp);
	if (status >= 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		free_all(prompt);
		free_pp(prompt->envp);
		clear_history();
		ft_close(fd_stdout);
		exit(g_exit_status);
	}
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
