#include "minishell.h"

void	*print_error(int err_type, char *param)
{
	ft_putstr_fd(param, 1);
	// write(1, ft_itoa(eorr_type), 1);
	if (err_type == QUOTE)
		write(1, "Unclosed quote\n", 15);
		// ft_putstr_fd("Quote error\n", 1); 

	// prompt->exit_status = err;
	// if (err_type == QUOTE)
	// 	ft_putstr_fd("Quote error\n", 2); 
    // else if (err_type == WCHAR)
	// 	ft_putstr_fd("Wrong input character: ", 2);
	// else if (err_type == NDIR)
	// 	ft_putstr_fd("No such file or directory: ", 2);
	// else if (err_type == NPERM)
	// 	ft_putstr_fd("Permission denied: ", 2);
	// else if (err_type == NCMD)
	// 	ft_putstr_fd("Command not found: ", 2);
	// else if (err_type == DUPERR)
	// 	ft_putstr_fd("Dup failed\n", 2);
	// else if (err_type == FORKERR)
	// 	ft_putstr_fd("Fork failed\n", 2);
	// else if (err_type == PIPERR)
	// 	ft_putstr_fd("Pipe error\n", 2);
	// else if (err_type == MEM)
	// 	ft_putstr_fd("No memory left on device\n", 2);
	// else if (err_type == IS_DIR)
	// 	ft_putstr_fd("Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		write(1, ": Not a directory\n", 18);

	// return (NULL);
}