#include "minishell.h"

int	minipipe(t_prompt *prompt)
{
	int	i;
	int	pipefd[2];

	i = 1;
	while (i <= prompt->nbr_request)
	{
		pipe(pipefd);
		prompt->requests[i].input_fd = pipefd[0];
		prompt->requests[i - 1].pipout_fd = pipefd[0];
		prompt->requests[i - 1].output_fd = pipefd[1];
		i += 1;
	}
	prompt->requests[i - 1].pipout_fd = -1;
	return (0);
}

int	process_cmd(t_request *request, t_prompt *prompt)
{
	int		result;

	result = 0;
	if (ft_strcmp(request->cmd, "echo") == 0)
		result = ft_echo(request, prompt);
	else if (ft_strcmp(request->cmd, "cd") == 0)
		result = ft_cd(request, prompt);
	else if (ft_strcmp(request->cmd, "pwd") == 0)
		result = ft_pwd(request, prompt);
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
	prompt->requests[0].nbr_token = 2;
	prompt->requests[0].input_fd = 0;
	prompt->requests[0].pipout_fd = -1;
	prompt->requests[0].pid = 0;
	prompt->requests[0].output_fd = 1;
	prompt->requests[0].cmd = ft_strdup("cd");
	prompt->requests[0].tab = (char **) malloc (3 * sizeof(char *));
	prompt->requests[0].tab[0] = ft_strdup("cd");
	prompt->requests[0].tab[1] = ft_strdup("srcs");
	prompt->requests[0].tab[2] = '\0';
	prompt->requests[0].token = ft_token_new("cd", 1);
	ft_token_add_back(&prompt->requests[0].token, ft_token_new("srcs", 2));

	prompt->requests[1].nbr_token = 2;
	prompt->requests[1].input_fd = 0;
	prompt->requests[1].pipout_fd = -1;
	prompt->requests[1].pid = 0;
	prompt->requests[1].output_fd = 1;
	prompt->requests[1].cmd = ft_strdup("pwd");
	prompt->requests[1].tab = (char **) malloc (3 * sizeof(char *));
	prompt->requests[1].tab[0] = ft_strdup("pwd");
	prompt->requests[1].tab[1] = ft_strdup("cmd");
	prompt->requests[1].tab[2] = '\0';
	prompt->requests[1].token = ft_token_new("pwd", 1);
	ft_token_add_back(&prompt->requests[1].token, ft_token_new("cmd", 2));

	// prompt->requests[2].nbr_token = 3;
	// prompt->requests[2].input_fd = 0;
	// prompt->requests[2].output_fd = 1;
	// prompt->requests[2].cmd = ft_strdup("ls");
	// prompt->requests[2].tab = (char **) malloc (3 * sizeof(char *));
	// prompt->requests[2].tab[0] = ft_strdup("ls");
	// prompt->requests[2].tab[1] = ft_strdup("-l");
	// prompt->requests[2].tab[2] = NULL;
	// prompt->requests[2].token = ft_token_new("ls", 1);
	return (0);
}

int	process(t_prompt *prompt)
{
	printf("[DEBUG] nbr_request: %d\n", prompt->nbr_request);
	if (prompt->nbr_request != 1)
		return (0);
	set_up(prompt);
	int		status;
	int		i;
	t_token	*token;

	status = 0;
	i = 0;
	prompt->prev_pipefd[0] = -1;
	prompt->prev_pipefd[1] = -1;
	while (i <= prompt->nbr_request)
	{
		// redirect_fd(&prompt->requests[i]);
		process_cmd(&prompt->requests[i++], prompt);
	}
	i = 0;
	ft_close(prompt->prev_pipefd[0]);
	ft_close(prompt->prev_pipefd[1]);
	while (i <= prompt->nbr_request)
	{
		waitpid(prompt->requests[i].pid, &status, WNOHANG);
		i ++;
	}
	free_tmp(prompt);
	printf("[DEBUG] status: %d, g_rsig.exit_status: %d\n", status, g_sig.exit_status);
	return (status);
}

int	free_tmp(t_prompt *prompt)
{
	int	j = 0;
	int i;
	while (j <= prompt->nbr_request)
	{
		i = -1;
		while (prompt->requests[j].tab[++i])
			free (prompt->requests[j].tab[i]);
		free (prompt->requests[j].cmd);
		free (prompt->requests[j].tab);
		printf("[DEBUG] input: %d, output: %d \n", prompt->requests[j].input_fd, prompt->requests[j].output_fd);
		ft_token_clear(prompt->requests[j].token);
		ft_close(prompt->requests[j].input_fd);
		ft_close(prompt->requests[j].output_fd);
		j += 1;
	}
	return (0);
}

// Question
//    yes | head
// -> no output
