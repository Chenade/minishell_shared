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
		result = exec_bin(cmd, prompt);
	return (result);
}

int	parsing_cmd(t_prompt *prompt)
{
	// t_token	*token;
	// t_token	*new_lst;
	// t_token	*new_head;

	// token = prompt->token;
	// while (token)
	// {
	// 	if (token->type < 5 || token->type > 10)
	// 	{
	// 		new_lst = token;
	// 		new_lst = new_lst->next;
	// 	}
	// 	// else
	// 	// {
	// 		if (!token->next)
	// 			break ;
	// 		token = token->next;
	// 	// }
	// }
	// prompt->token = new_lst;
	return (0);
}

int	pre_process(t_prompt *prompt)
{
	prompt->output_fd = 0;
	prompt->input_fd = 0;
	prompt->result = NULL;
	print_token(prompt->token);
	redirect_output(prompt);
	if (g_sig.exit_status)
		return (g_sig.exit_status);
	redirect_input(prompt);
	if (g_sig.exit_status)
		return (g_sig.exit_status);
	redirect_input2(prompt);
	if (g_sig.exit_status)
		return (g_sig.exit_status);
	parsing_cmd(prompt);
	if (g_sig.exit_status)
		return (g_sig.exit_status);
	print_token(prompt->token);
}

int	process(t_prompt *prompt)
{
	int		status;
	int		i;
	t_token	*token;

	status = 0;
	i = 0;
	pre_process(prompt);
	if (g_sig.exit_status)
		return (g_sig.exit_status);
	token = prompt->token;
	while (token && !status)
	{
		if (token->type == 1)
			status = builtin_cmd(token->str, i, prompt);
		if (!token->next)
			break ;
		token = token->next;
		i += 1;
	}
	printf("[DEBUG] status: %d, g_sig.exit_status: %d\n", status, g_sig.exit_status);
	return (status);
}
