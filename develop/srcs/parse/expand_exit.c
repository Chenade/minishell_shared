#include "minishell.h"

int	exit_strlen(void)
{
	char	*tmp;
	int		len;

	tmp = ft_itoa(g_exit_status);
	len = ft_strlen(tmp);
	free (tmp);
	return (len);
}

int expand_exit(char *new_out, int nout_i)
{
	char	*tmp;

	tmp = ft_itoa(g_exit_status);
	insert_str(new_out, &nout_i, tmp, ft_strlen(tmp));
	free (tmp);
	return (nout_i);
}