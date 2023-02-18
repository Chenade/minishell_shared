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
		free_matrix(&p->envp);
		exit(1);
	}
	if (pid == CHILD)
	{
		free_matrix(&p->envp);
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

int	minishell(char **out, t_prompt *prompt)
{
	if (*out[0] != '\0')
		add_history(*out);
	if (!*out[0] || !pre_check(*out, prompt))
	{
		*out = expansion(*out, prompt->envp);
		if (!*(out))
			return (1);
		if (separate_pipe(*out, prompt))
			return (1);
		printf("  out : %s\n", *out);
		parse_cmd(*out);
		printf("> out : %s\n", *out);
		printf("**nbr_request : %d\n", prompt->nbr_request);
		if(fill_token(*out, prompt))
			return (1);
		// check_args(out, &prompt);
		g_sig.exit_status = 0;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char				*out;
	t_prompt			prompt;
	
	prompt = init_prompt(argv, envp);
	while (42)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		out = readline("minishell $ ");
		if (!out)
			break;
		if (!minishell(&out, &prompt))
			free_readline (&out, &prompt);
		free_token(&(prompt.token));
	}
	free_all(&prompt);
	exit (g_sig.exit_status);
}