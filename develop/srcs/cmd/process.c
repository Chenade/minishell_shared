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

int	exec_cmd(t_request *request, t_prompt *prompt, int i)
{
	int		ret;

	pipe(prompt->pipefd);
	request->pid = fork();
	if (request->pid == 0)
	{
		set_signal();
		if (prompt->nbr_request != request->id)
			dup2(prompt->pipefd[WRITEEND], STDOUT_FILENO);
		if (request->id != 1)
			dupnclose(prompt->prev_pipefd, STDIN_FILENO);
		close(prompt->pipefd[READEND]);
		close(prompt->pipefd[WRITEEND]);
		redirection(request, prompt);
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
			g_exit_status = WEXITSTATUS(status);
	}
}

int	process(t_prompt *prompt)
{
	int		status;
	int		i;
	t_token	*token;

	status = 0;
	i = -1;
	prompt->prev_pipefd = -1;
	while (++i < prompt->nbr_request)
		post_parse(&prompt->requests[i], i);
	i = -1;
	if (prompt->nbr_request == 1 && is_builtin(prompt->requests[0].cmd))
		dispatch_cmd(&prompt->requests[0], prompt);
	else
		while (++i < prompt->nbr_request)
			exec_cmd(&prompt->requests[i], prompt, i);
	ft_wait(prompt);
	if (prompt->nbr_request > 1 || !is_builtin(prompt->requests[0].cmd))
		close(prompt->pipefd[0]);
	printf("[DEBUG] g_exit_status: %d\n", g_exit_status);
	return (status);
}
