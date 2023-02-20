/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:12:50 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/18 04:20:49 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig g_sig;

void	mini_getpid(t_prompt *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		print_error(FORKERR, NULL, NULL);
		free_pp(p->envp);
		exit(1);
	}
	if (pid == CHILD)
	{
		free_pp(p->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
	g_sig.pid = pid - 1;
}

void	sigint_handler(int sig)		// need to change exit_code -> 130;
{
	if (sig == SIGINT)
	{
		g_sig.exit_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 0);		//set string from readline as ""
		rl_on_new_line();			//set next line while readline
	}
}

int	minishell(char *out, t_prompt *prompt)
{
	int	status;
	char *cmd;

	cmd = ft_strdup(out);
	out = expansion(out, prompt->envp);
	if (out)
	{
		add_history(cmd);
		free(cmd);
		status = pre_check(out, prompt);
		parse_cmd(out, prompt->envp);
		if (!status)
		{
			// if (!(out))
			// 	return (1);
			if (fill_request(out, prompt))
				return (1);
			if (process(prompt))
				return (1);
			g_sig.exit_status = 0;
		}
	}
	else
	{
		free(cmd);
		return (1);
	}
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	char				*out;
	t_prompt			prompt;
	
	init_prompt(argv, envp, &prompt);
	while (42)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		out = readline("minishell $ ");
		if (!out)
			break;
		if (!minishell(out, &prompt))
			free_all(&prompt);
		// free_readline (&out, &prompt);
	}
	free_pp(prompt.envp);
	exit (g_sig.exit_status);
}