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

int	g_exit_status;

t_prompt	*starton(void)
{
	static t_prompt	prompt;

	return (&prompt);
}

int	minishell(char *out, t_prompt *prompt)
{
	int		status;
	char	*cmd;

	cmd = ft_strdup(out);
	out = expansion(out, prompt->envp);
	if (out)
	{
		add_history(cmd);
		free(cmd);
		status = pre_check(out, prompt);
		if (!status)
		{
			parse_cmd(out, prompt->envp);
			if (fill_request(out, prompt))
				return (1);
			process(prompt);
		}
		else
			free(out);
	}
	else
		return (free(cmd), 1);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	char				*out;
	t_prompt			*prompt;

	prompt = starton();
	init_prompt(argv, envp, prompt);
	out = NULL;
	g_exit_status = 0;
	while (42)
	{
		set_signal();
		out = readline("minishell $ ");
		if (!out)
			break ;
		if (!minishell(out, prompt))
			free_all(prompt);
	}
	free_pp(prompt->envp);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit (g_exit_status);
}
