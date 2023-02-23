#include "minishell.h"

void	sigint_process_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_exit_status = 130;
	}
}

void	sigquit_process_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_exit_status = 131;
	}
}

void	signal_process(void)
{
	signal(SIGINT, sigint_process_handler);
	signal(SIGQUIT, sigquit_process_handler);
}

void	sigint_handler(int sig)		// need to change exit_code -> 130;
{
	char *str;

	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	set_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}