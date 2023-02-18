/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:12:50 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/18 03:29:46 by jischoi          ###   ########.fr       */
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
	g_sig.exit_status = 0;
	prompt.has_pipe = 0;
	prompt.output_fd = 0;
	prompt.input_fd = 0;
	prompt.envp = dup_matrix(envp);
	prompt.token = NULL;
	mini_getpid(&prompt);
	prompt = init_envp(prompt, str, argv);
	return (prompt);
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

int	is_sep(char s)
{
	if (s == '<' || s == '>' || s == '|' || s == ' ')
		return (1);
	return (0);
}

int	is_quot(char s)
{
	if (s == '\'' || s == '\"')
		return (1);
	return (0);
}

void	rm_space_sep(char *cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		if ((is_sep(*cmd) && *(cmd - 1) == ' ') && ++i)
			*(cmd - 1) = *(cmd + i - 1);
		else if ((*(cmd) == ' ' && is_sep(*(cmd - 1))) && ++i)
			*(cmd) = *(cmd + i);
		else
			cmd++;
		*(cmd) = *(cmd + i);
	}
}

void	filter_cmd(char *cmd)
{
	int	i;
	char quot;
	char *tmp;

	i = 0;
	quot = '\0';
	tmp = cmd;
	while (*cmd == ' ')
		cmd++;
	while (*cmd)
	{
		if (!quot && is_quot(*cmd) && ++i)
			quot = *cmd;
		else if (quot && (*cmd == quot) && ++i)
			quot = '\0'; 
		else
			cmd++;
		*cmd = *(cmd + i);
	}
	cmd = tmp;
	rm_space_sep(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char				*out;
	t_prompt			prompt;
	
	prompt = init_prompt(argv, envp);
	while (argv && argc)
	{
		prompt.has_pipe = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		out = readline("minishell $ ");
		if (!out)
			break;
		if (out[0] != '\0')
			add_history(out);
		if (!out[0] || !pre_check(out))
		{
			out = expansion(out, prompt.envp);
			// todo if out = NULL, malloc error
			printf("  out : %s\n", out);
			filter_cmd(out);
			printf("> out : %s\n", out);
			// printf("BEFORE RM : %s\n", out);
			// rm_space_sep(out);
			// printf("AFT RM : %s\n", out);
			// check_args(out, &prompt);
			g_sig.exit_status = 0;
		}
		free (out);
	}
	free_all(&prompt);
	exit (g_sig.exit_status);
}