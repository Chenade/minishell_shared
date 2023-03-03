/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:09:45 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/28 17:30:38 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_cmd(t_prompt *prompt, int fd_stdout, int status)
{
	dupnclose(fd_stdout, STDOUT_FILENO);
	if (!(prompt->nbr_request == 1 && is_builtin(prompt->requests[0].cmd)))
	{
		free_all(prompt);
		free_pp(prompt->envp);
		clear_history();
	}
	if (status == -1)
		status = 1;
	return (status);
}

int	dispatch_cmd(t_request *request, t_prompt *prompt)
{
	int		result;
	int		fd_stdout;

	fd_stdout = dup(STDOUT_FILENO);
	if (redirection(request, prompt, fd_stdout))
		return (free_cmd(prompt, fd_stdout, 1));
	if (!request->cmd)
		return (free_cmd(prompt, fd_stdout, 1));
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
	else if (ft_strcmp(request->cmd, "exit") == 0)
		result = exit_minishell(request, prompt, fd_stdout);
	else
		result = exec_bin(request, prompt);
	return (free_cmd(prompt, fd_stdout, result));
}

int	exec_cmd_child(t_request *request, t_prompt *prompt, int i)
{
	(void) i;
	signal_process();
	if (prompt->nbr_request != request->id)
		dup2(prompt->pipefd[WRITEEND], STDOUT_FILENO);
	if (request->id != 1)
		dupnclose(prompt->prev_pipefd, STDIN_FILENO);
	ft_close(prompt->pipefd[READEND]);
	ft_close(prompt->pipefd[WRITEEND]);
	exit (dispatch_cmd(request, prompt));
}

int	exec_cmd(t_request *request, t_prompt *prompt, int i)
{
	pipe(prompt->pipefd);
	request->pid = fork();
	if (request->pid < 0)
		return (print_error(FORKERR, request->cmd, NULL));
	else if (request->pid == 0)
		exec_cmd_child(request, prompt, i);
	else
	{
		signal(SIGINT, SIG_IGN);
		ft_close (prompt->pipefd[WRITEEND]);
		if (prompt->prev_pipefd != -1)
			ft_close(prompt->prev_pipefd);
		prompt->prev_pipefd = prompt->pipefd[READEND];
	}
	return (0);
}

int	process(t_prompt *prompt)
{
	int		status;
	int		i;

	status = 0;
	i = -1;
	prompt->prev_pipefd = -1;
	while (++i < prompt->nbr_request)
		post_parse(&prompt->requests[i], i);
	here_doc(prompt);
	i = -1;
	if (prompt->nbr_request == 1 && is_builtin(prompt->requests[0].cmd))
		return (g_exit_status = dispatch_cmd(&prompt->requests[0], prompt));
	else
		while (++i < prompt->nbr_request)
			exec_cmd(&prompt->requests[i], prompt, i);
	ft_wait(prompt);
	if (prompt->nbr_request > 1 || !is_builtin(prompt->requests[0].cmd))
		ft_close(prompt->pipefd[0]);
	return (status);
}
