/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:12:50 by ykuo              #+#    #+#             */
/*   Updated: 2023/01/31 12:26:16 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status;

void	mini_getpid(t_prompt *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)			// fork failed
	{
		print_error(FORKERR, NULL);
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
}

t_prompt	init_envp(t_prompt prompt, char *str, char **argv)
{
	char	*num;
	
	str = getcwd(NULL, 0);
	prompt.envp = set_env("PWD", str, prompt.envp, 3);
	free(str);
	str = get_env("SHLVL", prompt.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.envp = set_env("SHLVL", num, prompt.envp, 5);
	free(num);
	str = get_env("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = set_env("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	free(str);
	str = get_env("_", prompt.envp, 1);
	if (!str)
		prompt.envp = set_env("_", argv[0], prompt.envp, 1);
	free(str);
	return (prompt);
}

t_prompt	init_prompt(char **argv, char **envp)
{
	t_prompt	prompt;
	char		*str;

	str = NULL;
	exit_status = 0;
	prompt.envp = dup_matrix(envp);
	mini_getpid(&prompt);
	prompt = init_envp(prompt, str, argv);
	return (prompt);
}

void	sigint_handler(int sig)		// need to change exit_code -> 130;
{
	if (sig == SIGINT)
	{
		exit_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 0);		//set string from readline as ""
		rl_on_new_line();			//set next line while readline
	}
}

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		exit_status = 131;
		ft_putstr_fd("Core dump\n", 2);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char				*out;
	t_prompt			prompt;
	
	prompt = init_prompt(argv, envp);
	while (argv && argc)
	{
		signal(SIGINT, sigint_handler);	// ctrl + C 
		// signal(SIGQUIT, sigquit_handler);
		signal(SIGQUIT, SIG_IGN);		// ctrl + \ : ignore it for now. i dont know what it suppose to be
		out = readline("minishell $ ");
		if (!check_args(out, &prompt))
			break ;
	}
	exit (exit_status);
}

