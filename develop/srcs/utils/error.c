/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 05:58:50 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/24 05:58:51 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_syntax_error(t_parse data, char *out)
{
	int	i;
	int	has_pipe;

	i = -1;
	has_pipe = 0;
	while (out[++i])
		if (out[i] == '|')
			has_pipe = 1;
	if (data.single_quote < 0)
		return (print_error(SYNERR, "", "'"));
	if (data.double_quote < 0)
		return (print_error(SYNERR, "", "\""));
	if (data.is_pipe < 0 && data.infile == 0 && data.outfile == 0 && has_pipe)
		return (print_error(SYNERR, "", "|"));
	if (data.is_pipe < 0 && data.infile == 0 && data.outfile == 0 && !has_pipe)
		return (print_error(SYNERR, "", &(out[i - 1])));
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
	ft_close(fd);
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
	else if (err_type == INV_ID)
		g_exit_status = 1;
}
// else if (err_type == DUPERR)
// 	ft_putstr_fd("Dup failed", STDERR_FILENO);
// else if (err_type == FORKERR)
// 	ft_putstr_fd("Fork failed", STDERR_FILENO);
// else if (err_type == PIPERR)
// 	ft_putstr_fd("Pipe error", STDERR_FILENO);

int	print_error(int err_type, char *cmd, char *param)
{
	set_exit_status(err_type);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (err_type == OP_NS)
		ft_putstr_fd(": Old Path not set.", STDERR_FILENO);
	else if (err_type == NDIR)
		ft_putstr_fd(": No such file or directory: ", STDERR_FILENO);
	else if (err_type == NPERM)
		ft_putstr_fd(": Permission denied", STDERR_FILENO);
	else if (err_type == NCMD)
		ft_putstr_fd(": \e[91mCommand not found\e[0m", STDERR_FILENO);
	else if (err_type == SYNERR)
		ft_putstr_fd(": syntax error near unexpected token: ", STDERR_FILENO);
	else if (err_type == TM_ARGS)
		ft_putstr_fd(": too many arguments", STDERR_FILENO);
	else if (err_type == MEM)
		ft_putstr_fd(": No memory left on device", STDERR_FILENO);
	else if (err_type == IS_DIR)
		ft_putstr_fd(": \e[91mIs a directory\e[0m", STDERR_FILENO);
	else if (err_type == NOT_DIR)
		ft_putstr_fd(":: Not a directory", STDERR_FILENO);
	else if (err_type == INV_ID)
		ft_putstr_fd(": not valid in this context: ", STDERR_FILENO);
	ft_putendl_fd(param, STDERR_FILENO);
	return (g_exit_status);
}
//  if (err_type == WCHAR)
// 	ft_putstr_fd("Wrong input character: ", STDERR_FILENO);
// else if (err_type == DUPERR)
// 	ft_putstr_fd("Dup failed", STDERR_FILENO);
// else if (err_type == FORKERR)
// 	ft_putstr_fd("Fork failed", STDERR_FILENO);
// else if (err_type == PIPERR)
// 	ft_putstr_fd("Pipe error", STDERR_FILENO);