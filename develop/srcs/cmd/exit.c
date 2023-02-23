#include "minishell.h"

void	ft_wait(t_prompt *prompt)
{
	int	status;
	int	i;

	i = -1;
	status = 0;
	while (++i < prompt->nbr_request)
	{
		waitpid(prompt->requests[i].pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

int	exit_minishell(t_request *request, t_prompt *prompt, int fd_stdout)
{
	int	status;

	status = 0;
	ft_wait(prompt);
	free_all(prompt);
	free_pp(prompt->envp);
	clear_history();
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_close(fd_stdout);
	g_exit_status = 0;
	exit(g_exit_status);
}
