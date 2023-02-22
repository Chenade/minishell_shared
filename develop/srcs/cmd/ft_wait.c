# include "minishell.h"

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
