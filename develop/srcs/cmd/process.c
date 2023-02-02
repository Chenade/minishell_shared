
#include "minishell.h"

t_token	*move_to(t_token *pre, int index)
{
	int		i;
	t_token	*token;
	
	i = 0;
	token = pre;
	while (token)
	{
		if (i == index)
			break ;
		i += 1;
		if (!token->next)
			break ;
		token = token->next;
	}
    return (token);
}
//  execve(const char *pathname, char *const argv[], char *const envp[]);
int	builtin_cmd(char *cmd, int i, t_prompt *prompt)
{
	int		result;

	result = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		result = ft_echo(i + 1, prompt);
	else if (ft_strcmp(cmd, "cd") == 0)
		result = ft_cd(i + 1, prompt);
	else if (ft_strcmp(cmd, "pwd") == 0)
		result = ft_pwd(prompt);
	else if (ft_strcmp(cmd, "export") == 0)
		result = ft_export(i + 1, prompt);
	else if (ft_strcmp(cmd, "unset") == 0)
		result = ft_unset(i + 1, prompt);
	else if (ft_strcmp(cmd, "env") == 0)
	{
		print_env(prompt->envp);
		result = 0;
	}
	else
	{
		// char *argv[] = {"ls", "-l"};
		// result =  execve("/usr/bin/ls", argv, prompt->envp);
		// printf("[DEBUG] %d\n", result);
		char *ac = {"cat", "Makefile"};
		int tmp = execve("/usr/bin/cat", ac, prompt->envp);
		printf("[DEBUG] %d\n", tmp);
		// exec_bin(cmd, prompt);
	}
	return (result);
}

int process(t_prompt *prompt)
{
    int		status;
	int		i;
	t_token	*token;
	
	status = 0;
	i = 0;
    token = prompt->token;
	prompt->result = NULL;
	print_token(token);
	while (token && !status)
	{
		if (token->type == 1)
			status = builtin_cmd(token->str, i, prompt);
		// if (token->type == 7 || token->type == 9)
		// 	status = redirect_output(prompt, token);
		if (!token->next)
			break;
		token = token->next;
		i += 1;
	}
    return (status);
}