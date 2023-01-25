#include "minishell.h"

void	*print_error(int err_type, char *param)
{
	// prompt->exit_status = err;
	if (err_type == QUOTE)
		ft_putstr_fd("Quote error\n", 2); 
    else if (err_type == WCHAR)
		ft_putstr_fd("Wrong input character: ", 2);
	else if (err_type == NDIR)
		ft_putstr_fd("No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("Permission denied: ", 2);
	else if (err_type == NCMD)
		ft_putstr_fd("Command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("Dup failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("Fork failed\n", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("Pipe error\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("No memory left on device\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("Not a directory: ", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}