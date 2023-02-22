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

void	sigint_handler(int sig)		// need to change exit_code -> 130;
{
	char *str;

	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.exit_status = 130;
		// ioctl(STDIN_FILENO, TIOCSTI, "\n");
		// if (rl_on_new_line() == -1)
		// 	exit(1);
		// rl_replace_line("", 0);		//set string from readline as ""
		// rl_on_new_line();			//set next line while readline
	}
}

void	set_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
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
			if (fill_request(out, prompt))
				return (1);
			if (process(prompt))
				return (1);
			g_sig.exit_status = 0;
		}
	}
	else
		return (free(cmd), 1);
	return (status);
}

// int	minishell_bk(char **out, t_prompt *prompt)
// {
// 	int	status;

// 	if (*out[0] != '\0')
// 		add_history(*out);
// 	status = 0;
// 	if (*out[0])
// 		status = pre_check(*out, prompt);
// 	// if (!*out[0] || !status)
// 	// {
// 	// 	*out = expansion(*out, prompt->envp);
// 	// 	if (!*(out))
// 	// 		return (1);
// 	// 	if (fill_request(out, prompt))
// 	// 		return (1);
// 	// 	if (process(prompt))
// 	// 			return (1);
// 	// 	g_sig.exit_status = 0;
// 	// }
// 	return (status);
// }

int	main(int argc, char **argv, char **envp)
{
	char				*out;
	t_prompt			prompt;
	
	init_prompt(argv, envp, &prompt);
	while (42)
	{
		set_signal();
		out = readline("minishell $ ");
		if (!out)
		{
			break;
		}
		if (!minishell(out, &prompt))
			free_all(&prompt);
		// free_readline (&out, &prompt);
	}
	free_pp(prompt.envp);
	exit (g_sig.exit_status);
}