#include "minishell.h"

int	print_syntax_error(t_parse data)
{
	if (data.single_quote < 0)
		return (print_error(SYNERR, "", "'"));
	if (data.double_quote < 0)
		return (print_error(SYNERR, "", "\""));
	if (data.is_pipe < 0 && data.infile == 0 && data.outfile == 0)
		return (print_error(SYNERR, "", "|"));
	if (data.infile > 0)
		return (print_error(SYNERR, "", "<"));
	if (data.outfile > 0)
		return (print_error(SYNERR, "", ">"));
	return (0);
}

int	print_redirect_error(int type, char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	if ((type == 7 || type == 9) && fd == -1 && folder == NULL)
		print_error(NPERM, path, NULL);
	if ((type == 6) && fd == -1 && folder == NULL)
		print_error(NDIR, path, NULL);
	else if (fd == -1 && folder != NULL)
		print_error(IS_DIR, path, NULL);
	if (folder)
		closedir(folder);
	close(fd);
	g_exit_status = 1;
	return (g_exit_status);
}

int	print_fd_error(char *path, char *cmd)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = NULL;
	if (path)
		folder = opendir(path);
	if (ft_strchr(path, '/') == NULL)
		print_error(NCMD, cmd, NULL);
	else if (fd == -1 && folder == NULL)
		print_error(NDIR, cmd, NULL);
	else if (fd == -1 && folder != NULL)
		print_error(IS_DIR, cmd, NULL);
	else if (fd != -1 && folder == NULL)
		print_error(NPERM, cmd, NULL);
	if (folder)
		closedir(folder);
	ft_close(fd);
	g_exit_status = 127;
	return (g_exit_status);
}

void	set_exit_status(int err_type)
{
	if (err_type == OP_NS)
		g_exit_status = 1;
	else if (err_type == NDIR)
		g_exit_status = 1;
	else if (err_type == NPERM)
		g_exit_status = 1;
	else if (err_type == NCMD)
		g_exit_status = 1;
	else if (err_type == SYNERR)
		g_exit_status = 2;
	else if (err_type == TM_ARGS)
		g_exit_status = 1;
	else if (err_type == MEM)
		g_exit_status = 2;
	else if (err_type == IS_DIR)
		g_exit_status = 1;
	else if (err_type == NOT_DIR)
		g_exit_status = 1;
}
// else if (err_type == DUPERR)
// 	ft_putstr_fd("Dup failed", 2);
// else if (err_type == FORKERR)
// 	ft_putstr_fd("Fork failed", 2);
// else if (err_type == PIPERR)
// 	ft_putstr_fd("Pipe error", 2);

int	print_error(int err_type, char *cmd, char *param)
{
	set_exit_status(err_type);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (err_type == OP_NS)
		ft_putstr_fd(": Old Path not set.", 2);
	else if (err_type == NDIR)
		ft_putstr_fd(": No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd(": Permission denied", 2);
	else if (err_type == NCMD)
		write(1, ": \e[91mCommand not found\e[0m", 29);
	else if (err_type == SYNERR)
		ft_putstr_fd(": syntax error near unexpected token: ", 2);
	else if (err_type == TM_ARGS)
		ft_putstr_fd(": too many arguments", 2);
	else if (err_type == MEM)
		ft_putstr_fd(": No memory left on device", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd(": \e[91mIs a directory\e[0m", 2);
	else if (err_type == NOT_DIR)
		write(1, ": Not a directory", 18);
	ft_putendl_fd(param, 2);
	return (g_exit_status);
}
//  if (err_type == WCHAR)
// 	ft_putstr_fd("Wrong input character: ", 2);
// else if (err_type == DUPERR)
// 	ft_putstr_fd("Dup failed", 2);
// else if (err_type == FORKERR)
// 	ft_putstr_fd("Fork failed", 2);
// else if (err_type == PIPERR)
// 	ft_putstr_fd("Pipe error", 2);