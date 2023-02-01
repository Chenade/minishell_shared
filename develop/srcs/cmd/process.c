
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

int	builtin_cmd(char *cmd, int i, t_prompt *prompt)
{
	int		result;

	result = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		result = ft_echo(i + 1, prompt);
	if (ft_strcmp(cmd, "cd") == 0)
		result = ft_cd(i + 1, prompt);
	else if (ft_strcmp(cmd, "pwd") == 0)
		result = ft_pwd(prompt);
	else if (ft_strcmp(cmd, "export") == 0)
		result = ft_export(i + 1, prompt);
	else if (ft_strcmp(cmd, "unset") == 0)
		result = ft_unset(i + 1, prompt);
	else if (ft_strcmp(cmd, "printenv") == 0)
	{
		print_env(prompt->envp);
		result = 0;
	}
	else
	{
		print_error(NCMD, cmd, NULL);
		result = 0;
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
	print_token(token);
	while (token && !status)
	{
		if (token->type == 1)
			status = builtin_cmd(token->str, i, prompt);
		if (!token->next)
			break;
		token = token->next;
		i += 1;
	}
    return (0);
}