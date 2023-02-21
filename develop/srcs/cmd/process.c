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
	return (result);
}

#define READEND 0
#define WRITEEND 1

void	dupnclose(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	ft_close(oldfd);
}

int	exec_cmd(t_request *request, t_prompt *prompt)
{
	int		ret;
	int		tmp;

	tmp = 0;
	pipe(prompt->pipefd);
	request->pid = fork();
	if (request->pid == 0)
	{
		close(prompt->pipefd[READEND]);
		// if is not first cmd
		if (prompt->prev_pipefd[READEND] != -1)
			dupnclose(prompt->prev_pipefd[READEND], STDIN_FILENO);
		// todo: if is not last cmd
		if (request->nbr_token != 1)
			dupnclose(prompt->pipefd[WRITEEND], STDOUT_FILENO);
		dispatch_cmd(request, prompt);
		free_all(prompt);
		free_pp(prompt->envp);
		clear_history();
		exit (0);
	}
	else
	{
		close(prompt->pipefd[WRITEEND]);
		close(prompt->pipefd[READEND]);
		ft_close(prompt->prev_pipefd[READEND]);
		ft_close(prompt->prev_pipefd[WRITEEND]);
		prompt->prev_pipefd[READEND] = prompt->pipefd[READEND];
		prompt->prev_pipefd[WRITEEND] = prompt->pipefd[WRITEEND];
	}
	return (0);
}

int	process_cmd(t_request *request)
{
	request->pid = 0;
	request->tab = NULL;
	// todo: redirect_fd(&prompt->requests[i]);

	return (0);
}

int	process(t_prompt *prompt)
{
	printf("[DEBUG] nbr_request: %d\n", prompt->nbr_request);
	int		status;
	int		i;
	t_token	*token;

	status = 0;
	i = 0;
	prompt->prev_pipefd[0] = -1;
	prompt->prev_pipefd[1] = -1;
	while (i < prompt->nbr_request)
	{
		process_cmd(&prompt->requests[i]);
		exec_cmd(&prompt->requests[i], prompt);
		print_token(prompt->requests[i++].token);
	}
	i = 0;
	ft_close(prompt->prev_pipefd[0]);
	ft_close(prompt->prev_pipefd[1]);
	while (i < prompt->nbr_request)
		waitpid(prompt->requests[i++].pid, &status, WNOHANG);
	printf("[DEBUG] status: %d, g_rsig.exit_status: %d\n", status, g_sig.exit_status);
	return (status);
}

// Question
//    yes | head
// -> no output


// int	set_up(t_prompt *prompt)
// {
// 	prompt->requests[0].nbr_token = 2;
// 	prompt->requests[0].input_fd = 0;
// 	prompt->requests[0].pipout_fd = -1;
// 	prompt->requests[0].pid = 0;
// 	prompt->requests[0].output_fd = 1;
// 	prompt->requests[0].cmd = ft_strdup("export");
// 	prompt->requests[0].tab = (char **) malloc (3 * sizeof(char *));
// 	prompt->requests[0].tab[0] = ft_strdup("export");
// 	prompt->requests[0].tab[1] = ft_strdup("test1=test1");
// 	prompt->requests[0].tab[2] = '\0';
// 	prompt->requests[0].token = ft_token_new("export", 1);
// 	ft_token_add_back(&prompt->requests[0].token, ft_token_new("tessst1=test1", 3));
// 	ft_token_add_back(&prompt->requests[0].token, ft_token_new("test2=test3", 3));

// 	prompt->requests[1].nbr_token = 2;
// 	prompt->requests[1].input_fd = 0;
// 	prompt->requests[1].pipout_fd = -1;
// 	prompt->requests[1].pid = 0;
// 	prompt->requests[1].output_fd = 1;
// 	prompt->requests[1].cmd = ft_strdup("unset");
// 	prompt->requests[1].tab = (char **) malloc (3 * sizeof(char *));
// 	prompt->requests[1].tab[0] = ft_strdup("unset");
// 	prompt->requests[1].tab[1] = ft_strdup("test1=test1");
// 	prompt->requests[1].tab[2] = '\0';
// 	prompt->requests[1].token = ft_token_new("unset", 1);
// 	ft_token_add_back(&prompt->requests[1].token, ft_token_new("test1", 4));

// 	// prompt->requests[2].nbr_token = 3;
// 	// prompt->requests[2].input_fd = 0;
// 	// prompt->requests[2].output_fd = 1;
// 	// prompt->requests[2].cmd = ft_strdup("ls");
// 	// prompt->requests[2].tab = (char **) malloc (3 * sizeof(char *));
// 	// prompt->requests[2].tab[0] = ft_strdup("ls");
// 	// prompt->requests[2].tab[1] = ft_strdup("-l");
// 	// prompt->requests[2].tab[2] = NULL;
// 	// prompt->requests[2].token = ft_token_new("ls", 1);
// 	return (0);
// }