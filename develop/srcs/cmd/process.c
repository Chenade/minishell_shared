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
		char *argv[] = {"ls", "-la", NULL};
		// result =  execve("/usr/bin/ls", argv, prompt->envp);
		// printf("[DEBUG] %d\n", result);
		char *ac[] = {"cat", "Makefile", NULL};
		int tmp = execve("/usr/bin/cat", argv, prompt->envp);
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
	prompt->output_fd = 1;
	prompt->input_fd = 0;
    token = prompt->token;
	prompt->result = NULL;
	print_token(token);

	redirect_output(prompt);
	if (g_sig.exit_status)
		return (g_sig.exit_status);
	
	redirect_input(prompt);
	if (g_sig.exit_status)
		return (g_sig.exit_status);
	
	// printf("[DEBUG] input_fd: %d, output_fd:%d\n", prompt->input_fd, prompt->output_fd);
	while (token && !status)
	{
		if (token->type == 1)
			status = builtin_cmd(token->str, i, prompt);
		if (!token->next)
			break;
		token = token->next;
		i += 1;
	}
	// printf("[DEBUG] status: %d\n", status);
    return (status);
}