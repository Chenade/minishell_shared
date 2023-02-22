#include "minishell.h"

void	init_envp(t_prompt *prompt, char *str, char **argv)
{
	char	*num;
	
	str = getcwd(NULL, 0);
	prompt->envp = set_env("PWD", str, prompt->envp, 3);
	free(str);
	str = get_env("SHLVL", prompt->envp, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt->envp = set_env("SHLVL", num, prompt->envp, 5);
	free(num);
	str = get_env("PATH", prompt->envp, 4);
	if (!str)
		prompt->envp = set_env("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt->envp, 4);
	free(str);
	str = get_env("_", prompt->envp, 1);
	if (!str)
		prompt->envp = set_env("_", argv[0], prompt->envp, 1);
	free(str);
}

void	init_prompt(char **argv, char **envp, t_prompt *prompt)
{
	char		*str;

	str = NULL;
	g_exit_status = 0;
	prompt->envp = dup_matrix(envp);
	prompt->clean = NULL;
	prompt->nbr_request = 0;
	prompt->requests = NULL;
	init_envp(prompt, str, argv);
}
