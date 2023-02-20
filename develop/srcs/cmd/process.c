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



// cat | ls -l
// cat | cat | ls -l

int	set_up(t_prompt *prompt)
{
	int		pipefd[2];
	// pipe(pipefd);

	int tmp = open("Makefile", O_RDONLY);
	close(tmp);
	prompt->requests[0].nbr_token = 1;
	prompt->requests[0].input_fd = 0;
	prompt->requests[0].pipout_fd = -1;
	prompt->requests[0].output_fd = 1;
	prompt->requests[0].cmd = ft_strdup("cat");
	prompt->requests[0].tab = (char **) malloc (3 * sizeof(char *));
	prompt->requests[0].tab[0] = ft_strdup("cat");
	prompt->requests[0].tab[1] = NULL;//
	// prompt->requests[0].tab[1] = ft_strdup("Makefile");
	prompt->requests[0].tab[2] = '\0';
	prompt->requests[0].token = ft_token_new("cat", 1);
	prompt->requests[0].token = ft_token_add_back(&prompt->requests[0].token, ft_token_new("-l", 1));

	prompt->requests[1].nbr_token = 2;
	prompt->requests[1].input_fd = 0;
	prompt->requests[1].pipout_fd = -1;
	prompt->requests[1].output_fd = 1;
	prompt->requests[1].cmd = ft_strdup("ls");
	prompt->requests[1].tab = (char **) malloc (3 * sizeof(char *));
	prompt->requests[1].tab[0] = ft_strdup("ls");
	// prompt->requests[1].tab[1] = ft_strdup("-l");
	prompt->requests[1].tab[1] = NULL;
	prompt->requests[1].token = ft_token_new("ls", 1);

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
	if (prompt->nbr_request != 1)
		return (0);
	set_up(prompt);
	int		status;
	int		i;
	t_token	*token;

	status = 0;
	i = 0;
	// minipipe(prompt);
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
		ft_token_clear(prompt->requests[j].token);
		// printf("[DEBUG] input: %d, output: %d \n", prompt->requests[j].input_fd, prompt->requests[j].output_fd);
		ft_close(prompt->requests[j].input_fd);
		ft_close(prompt->requests[j].output_fd);
		j += 1;
	}
	return (0);
}

// Question
//    yes | head
// -> no output
