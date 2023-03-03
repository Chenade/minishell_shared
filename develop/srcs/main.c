/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:12:50 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/26 04:08:14 by jischoi          ###   ########.fr       */
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

	status = pre_check(out, prompt);
	add_history(out);
	if (!status)
	{
		out = expansion(out, prompt->envp);
		turn_sep(out);
		if (out)
		{
			parse_cmd(out, prompt->envp);
			if (fill_request(out, prompt))
				return (1);
			process(prompt);
		}
		else
			free(out);
	}
	return (status);
}

int	skip_emptycmd(char *out)
{
	int	i;

	i = 0;
	if (!ft_strlen(out))
		return (1);
	while (out[i] == ' ')
		i++;
	if (out[i])
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char				*out;
	t_prompt			*prompt;

	(void) argc;
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
		if (skip_emptycmd(out))
			continue ;
		if (!minishell(out, prompt))
			free_all(prompt);
	}
	free_pp(prompt->envp);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit (g_exit_status);
}
