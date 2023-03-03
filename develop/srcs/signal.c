/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:07:44 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/26 05:26:29 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	sigint_process_handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		ft_putstr_fd("\n", 1);
// 		g_exit_status = 130;
// 	}
// }

// void	sigquit_process_handler(int sig)
// {
// 	if (sig == SIGQUIT)
// 	{
// 		ft_putstr_fd("Quit (core dumped)\n", 1);
// 		g_exit_status = 131;
// 	}
// }

// void	signal_process(void)
// {
// 	signal(SIGINT, sigint_process_handler);
// 	signal(SIGQUIT, sigquit_process_handler);
// }

void	sigignore_handler(int sig)
{
	if (sig == SIGINT)
		g_exit_status = 130;
	else if (sig == SIGQUIT)
		g_exit_status = 131;
}

void	signal_process(void)
{
	signal(SIGINT, sigignore_handler);
	signal(SIGQUIT, sigignore_handler);
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	set_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
