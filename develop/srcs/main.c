/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:12:50 by ykuo              #+#    #+#             */
/*   Updated: 2023/01/31 14:41:17 by jischoi          ###   ########.fr       */
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
	prompt.envp = dup_matrix(envp);
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

// int	main(int argc, char **argv, char **envp)
// {
// 	char				*out;
// 	t_prompt			prompt;
	
// 	prompt = init_prompt(argv, envp);
// 	while (argv && argc)
// 	{
// 		prompt.has_pipe = 0;
// 		signal(SIGINT, sigint_handler);
// 		signal(SIGQUIT, SIG_IGN);
// 		out = readline("minishell $ ");
// 		if (!check_args(out, &prompt))
// 			break ;
// 		else
// 			free_all(&prompt);
// 	}
// 	exit (g_sig.exit_status);
// }

int	pre_check(char *out)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = -1;
	double_quote = 1;
	single_quote = 1;
	if (out[0] == '|' || out[ft_strlen(out) - 1] == '|')
		return (1);	//printf("[DEBUG]pipe error\n");
	while (out[++i])
	{
		if (out[i] == 34 && single_quote > 0)
			double_quote *= -1;
		if (out[i] == 39 && double_quote > 0)
			single_quote *= -1;
		if (out[i] == '|' && out[i + 1] == '|')
			return (1);
	}
	if (single_quote < 0 || double_quote < 0)
		return (1);
	return (0);
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
		if (!pre_check(out))
		{
			check_args(out, &prompt);
			g_sig.exit_status = 0;
		}
		free (out);
	}
	// free_all(&prompt);
	exit (g_sig.exit_status);
}

// starting  by |
// finishing by |
// more than 1x | in a row so a||a its not ok but a|a|a is ok


// <<< 
// <>
// ><
// when you <, <<, >> or > you have to have a filename after, either its stick together or there as may many space in between

// for the rule of "" '', you dont care what is in the middle


//be sure not have any error when you do valgrind -s

//case that should not work:
//fdsfds |
//|
//fsdfsd ||
//>> fdsfds fds >>
//"fsdfds "  >> <<
//echo > > fdsfds
//echo <> fsdfd
//echo <<>
//echo ><
//<
//"fsfds |" ""|
//fdsfdssd|>|fsfsdf
//f|       <<    |fds
//ffd<|fdfd
//"fdsfdsfsfds "'fdsfds'"|""""|
// '<'""|<


//case that should work:
//<"|"
//"fsdfds>>"<">>>"
//""|da|a|>a|""
//"fdsfds"|'|'|'|'
//""f"f">>lol"|"
// <<"<" ->it work and the multi is normal because its an heredoc
//>">"<"<"


// export a="cat filea fileb"
// $a => return filea not found