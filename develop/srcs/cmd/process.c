/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:09:45 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/21 09:09:46 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char	*cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

int	dispatch_cmd(t_request *request, t_prompt *prompt)
{
	int		result;

	result = 0;
	if (ft_strcmp(request->cmd, "echo") == 0)
		result = ft_echo(request, prompt);
	else if (ft_strcmp(request->cmd, "cd") == 0)
		result = ft_cd(request, prompt);
	else if (ft_strcmp(request->cmd, "pwd") == 0)
		result = ft_pwd(request, prompt);
	else if (ft_strcmp(request->cmd, "export") == 0)
		result = ft_export(request, prompt);
	else if (ft_strcmp(request->cmd, "unset") == 0)
		result = ft_unset(request, prompt);
	else if (ft_strcmp(request->cmd, "env") == 0)
		result = print_env(prompt->envp);
	else
		result = exec_bin(request, prompt);
	if (prompt->nbr_request > 1 || !is_builtin(request->cmd))
	{
		free_all(prompt);
		free_pp(prompt->envp);
		clear_history();
	}
	return (result);
}

#define READEND 0
#define WRITEEND 1

void	dupnclose(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	ft_close(oldfd);
}

int	exec_cmd(t_request *request, t_prompt *prompt, int i)
{
	int		ret;
	int		tmp;

	tmp = 0;
	pipe(prompt->pipefd);
	request->pid = fork();
	if (request->pid == 0)
	{
		if (prompt->nbr_request != request->id)
			dup2(prompt->pipefd[WRITEEND], STDOUT_FILENO);
		if (request->id != 1)
			dupnclose(prompt->prev_pipefd, STDIN_FILENO);
		close(prompt->pipefd[READEND]);
		close(prompt->pipefd[WRITEEND]);
		// todo: redirect_fd(request);
		exit (dispatch_cmd(request, prompt));
	}
	else
	{
		close (prompt->pipefd[WRITEEND]);
		if (prompt->prev_pipefd != -1)
			close(prompt->prev_pipefd);
		prompt->prev_pipefd = prompt->pipefd[READEND];
	}
	return (0);
}

int	ft_array_push(char ***array, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	if (*array == NULL)
	{
		*array = (char **)malloc(sizeof(char *) * 2);
		(*array)[0] = ft_strdup(str);
		(*array)[1] = NULL;
		return (0);
	}
	while ((*array)[i] != NULL)
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*array)[i] != NULL)
	{
		tmp[i] = ft_strdup((*array)[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	free_pp(*array);
	*array = tmp;
	return (0);
}

int	post_parse(t_request *request, int index)
{
	int		i;
	int		redirect;
	t_token	*token;

	i = 0;
	redirect = 0;
	request->pid = 0;
	request->id = index + 1;
	request->tab = NULL;
	token = request->token;
	while (i < request->nbr_token)
	{
		if (token->type == 1)
		{
			request->cmd = ft_strdup(token->str);
			ft_array_push(&request->tab, token->str);
		}
		else if ((token->type == 2 || token->type == 5) && redirect == 0)
			ft_array_push(&request->tab, token->str);
		else if (token->type == 2 && redirect > 0)
			redirect -= 1;
		else if (token->type > 5 && token->type < 10)
			redirect = 1;
		token = token->next;
		i++;
	}
	i = -1;
	return (0);
}

void	ft_wait(t_prompt *prompt)
{
	int		status;
	int		i;

	i = -1;
	status = 0;
	while (++i < prompt->nbr_request)
	{
		waitpid(prompt->requests[i].pid, &status, 0);
		if (WIFEXITED(status))
			g_sig.exit_status = WEXITSTATUS(status);
	}
}

int	process(t_prompt *prompt)
{
	printf("[DEBUG] nbr_request: %d\n", prompt->nbr_request);
	int		status;
	int		i;
	t_token	*token;

	status = 0;
	i = -1;
	prompt->prev_pipefd = -1;
	while (++i < prompt->nbr_request)
		post_parse(&prompt->requests[i], i);
	if (prompt->nbr_request == 1 && is_builtin(prompt->requests[0].cmd))
		dispatch_cmd(&prompt->requests[0], prompt);
	else
	{
		i = -1;
		while (++i < prompt->nbr_request)
			status = exec_cmd(&prompt->requests[i], prompt, i);
	}
	ft_wait(prompt);
	if (prompt->nbr_request > 1 || !is_builtin(prompt->requests[0].cmd))
		close(prompt->pipefd[0]);
	printf("[DEBUG] status: %d, g_rsig.exit_status: %d\n", status, g_sig.exit_status);
	return (status);
}
