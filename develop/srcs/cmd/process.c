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
		result = print_env(prompt->envp);
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

// int	pre_process(t_prompt *prompt)
// {
// 	prompt->result = NULL;
// 	print_token(prompt->token);
// 	redirect_output(prompt);
// 	if (g_sig.exit_status)
// 		return (g_sig.exit_status);
// 	redirect_input(prompt);
// 	if (g_sig.exit_status)
// 		return (g_sig.exit_status);
// 	redirect_input2(prompt);
// 	if (g_sig.exit_status)
// 		return (g_sig.exit_status);
// 	parsing_cmd(prompt);
// 	if (g_sig.exit_status)
// 		return (g_sig.exit_status);
// 	print_token(prompt->token);
// 	return (0);
// }

int	set_up(t_prompt *prompt)
{
	printf("[DEBUG] prompt->clean: %s\n", prompt->clean);
	prompt->requests[0].nbr_token = 2;
	prompt->requests[0].tab = (char **) malloc (3 * sizeof(char *));
	prompt->requests[0].tab[0] = ft_strdup("cat");
	prompt->requests[0].tab[1] = ft_strdup("Makefile");
	prompt->requests[0].tab[2] = '\0';

	prompt->requests[1].nbr_token = 2;
	prompt->requests[1].tab = (char **) malloc (3 * sizeof(char *));
	prompt->requests[1].tab[0] = ft_strdup("cat");
	prompt->requests[1].tab[1] = ft_strdup("Makefile");
	prompt->requests[1].tab[2] = '\0';

	return (0);
}

int	process(t_prompt *prompt)
{
	set_up(prompt);
	int		status;
	int		i;
	t_token	*token;

	status = 0;
	i = 0;
	// // pre_process(prompt);
	// if (g_sig.exit_status)
	// 	return (g_sig.exit_status);
	// token = prompt->token;
	// while (token && !status)
	// {
	// 	if (token->type == 1)
	// 		status = builtin_cmd(token->str, i, prompt);
	// 	if (!token->next)
	// 		break ;
	// 	token = token->next;
	// 	i += 1;
	// }
	free_tmp(prompt);
	printf("[DEBUG] status: %d, g_sig.exit_status: %d\n", status, g_sig.exit_status);
	return (status);
}


int	free_tmp(t_prompt *prompt)
{

	printf("[DEBUG] prompt->nbr_request: %d\n", prompt->nbr_request);
	int	j = 0;
	int i;
	while (j <= prompt->nbr_request)
	{
		i = -1;
		while (prompt->requests[j].tab[++i])
		{
			printf("[DEBUG] prompt->requests[0].tab[%d]: %s\n", 0, prompt->requests[j].tab[i]);
			free (prompt->requests[j].tab[i]);
		}
		free (prompt->requests[j].tab);
		j += 1;
	}
	
	return (0);
}
