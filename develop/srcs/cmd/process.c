#include "minishell.h"

int		minipipe(t_request *request, t_prompt *prompt)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		int i = dup2(pipefd[0], 0);
		printf("[%d]\n", i);
		request->input_fd = pipefd[0];
		prompt->pid = -1;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], 1);
		request->output_fd = pipefd[1];
		prompt->pid = pid;
		return (1);
	}
}

int	process_cmd(t_request *request, t_prompt *prompt)
{
	int		result;

	result = 0;
	if (ft_strcmp(request->cmd, "echo") == 0)
		result = ft_echo(request, prompt);
	// else if (ft_strcmp(cmd, "cd") == 0)
	// 	result = ft_cd(i + 1, prompt);
	// else if (ft_strcmp(cmd, "pwd") == 0)
	// 	result = ft_pwd(prompt);
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	result = ft_export(i + 1, prompt);
	// else if (ft_strcmp(cmd, "unset") == 0)
	// 	result = ft_unset(i + 1, prompt);
	// else if (ft_strcmp(cmd, "env") == 0)
	// 	result = print_env(prompt->envp);
	else
		result = exec_bin(request, prompt);
	return (result);
}

int	set_up(t_prompt *prompt)
{
	printf("[DEBUG] prompt->clean: %s\n", prompt->clean);
	printf("[DEBUG] prompt->nbr_request: %d\n", prompt->nbr_request);

	prompt->requests[0].nbr_token = 2;
	prompt->requests[0].input_fd = dup(0);
	prompt->requests[0].output_fd = dup(1);
	prompt->requests[0].cmd = ft_strdup("ls");
	prompt->requests[0].tab = (char **) malloc (3 * sizeof(char *));
	prompt->requests[0].tab[0] = ft_strdup("ls");
	prompt->requests[0].tab[1] = ft_strdup("-l");
	prompt->requests[0].tab[2] = '\0';
	prompt->requests[0].token = ft_token_new("ls", 1);
	prompt->requests[0].token = ft_token_add_back(&prompt->requests[0].token, ft_token_new("-l", 1));

	prompt->requests[1].nbr_token = 2;
	prompt->requests[1].input_fd = dup(0);
	prompt->requests[1].output_fd = dup(1);
	prompt->requests[1].cmd = ft_strdup("echo");
	prompt->requests[1].tab = (char **) malloc (3 * sizeof(char *));
	prompt->requests[1].tab[0] = ft_strdup("echo");
	prompt->requests[1].tab[1] = ft_strdup("NAME");
	prompt->requests[1].tab[2] = '\0';
	prompt->requests[1].token = ft_token_new("echo", 1);
	// prompt->requests[1].token = ft_token_add_back(&prompt->requests[0].token, ft_token_new("NAME", 1));

	// prompt->requests[1].nbr_token = 2;
	// prompt->requests[1].cmd = ft_strdup("grep");
	// prompt->requests[1].tab = (char **) malloc (3 * sizeof(char *));
	// prompt->requests[1].tab[0] = ft_strdup("grep");
	// prompt->requests[1].tab[1] = ft_strdup("NAME");
	// prompt->requests[1].tab[2] = '\0';
	// prompt->requests[1].token = ft_token_new("grep", 1);
	// prompt->requests[0].token = ft_token_add_back(&prompt->requests[0].token, ft_token_new("NAME", 1));


	return (0);
}

void	reset_std(t_request *request)
{
	dup2(request->input_fd, 0);
	dup2(request->output_fd, 1);
}

int	process(t_prompt *prompt)
{
	if (prompt->nbr_request != 1)
		return (0);
	set_up(prompt);
	int		status;
	int		i;
	t_token	*token;

	status = 0;
	i = 0;
	while (i <= prompt->nbr_request)
	{
		// reset_std(&prompt->requests[i]);
		if (i > 0)
			minipipe (&prompt->requests[i], prompt);
		process_cmd(&prompt->requests[i], prompt);
		ft_close(prompt->requests[i].input_fd);
		ft_close(prompt->requests[i].output_fd);
		i += 1;
	}
	free_tmp(prompt);
	printf("[DEBUG] status: %d, g_rsig.exit_status: %d\n", status, g_sig.exit_status);
	return (status);
}

int	free_tmp(t_prompt *prompt)
{

	// printf("[DEBUG] ====== End Process =====\n");
	int	j = 0;
	int i;
	while (j <= prompt->nbr_request)
	{
		i = -1;
		// printf("\n[DEBUG] prompt->requests[%d].cmd: %s\n", j, prompt->requests[j].cmd);
		while (prompt->requests[j].tab[++i])
		{
			// printf("[DEBUG] prompt->requests[%d].tab[%d]: %s\n",j,  i, prompt->requests[j].tab[i]);
			free (prompt->requests[j].tab[i]);
		}
		free (prompt->requests[j].cmd);
		free (prompt->requests[j].tab);
		ft_token_clear(prompt->requests[j].token);
		j += 1;
	}
	// printf("[DEBUG] ====== End Process =====\n");
	return (0);
}
