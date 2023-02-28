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
	if (data.has_semico > 0)
		return (print_error(SYNERR, "", ";"));
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

int	print_fd_error(char *path, char *cmd, int type)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = NULL;
	if (path && fd < 0)
		folder = opendir(path);
	if (fd > 0)
		print_error(NOT_DIR, cmd, NULL);
	else if (type)
		print_error(NCMD, cmd, NULL);
	else if (fd == -1 && folder == NULL && !type)
		print_error(NDIR, cmd, NULL);
	else if (fd == -1 && folder != NULL && !type)
		print_error(IS_DIR, cmd, NULL);
	else if (ft_strchr(path, '/') == NULL && !type)
		print_error(NPERM, cmd, NULL);
	if (folder)
		closedir(folder);
	ft_close(fd);
	g_exit_status = 1;
	return (g_exit_status);
}

void	set_exit_status(int err_type, char *cmd)
{
	if (err_type == OP_NS)
		printf("minishell: %s : Old Path not set.\n", cmd);
	if (err_type == NOT_DIR)
		printf("minishell: %s :Not a directory.\n", cmd);
	if (err_type == ABRT)
		printf("minishell: %s : ambiguous redirect.\n", cmd);
	if (err_type == FORKERR)
		ft_putstr_fd("Fork failed", STDERR_FILENO);
	if (err_type == OP_NS || err_type == NDIR)
		g_exit_status = 1;
	else if (err_type == NPERM || err_type == ABRT)
		g_exit_status = 1;
	else if (err_type == NCMD || err_type == IS_DIR)
		g_exit_status = 1;
	else if (err_type == SYNERR || err_type == FORKERR)
		g_exit_status = 2;
	else if (err_type == TM_ARGS)
		g_exit_status = 1;
	else if (err_type == MEM)
		g_exit_status = 2;
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
	int	fd;

	set_exit_status(err_type, cmd);
	fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (err_type == NDIR)
		printf("minishell: %s : No such file or directory.\n", cmd);
	else if (err_type == NPERM)
		printf("minishell: %s : Permission denied.\n", cmd);
	else if (err_type == NCMD)
		printf("minishell: %s : \e[91mCommand not found\e[0m\n", cmd);
	else if (err_type == SYNERR)
		printf("minishell: %s : syntax error near unexpected token: %s\n",
			cmd, param);
	else if (err_type == TM_ARGS)
		printf("minishell: %s : too many arguments.\n", cmd);
	else if (err_type == MEM)
		printf("minishell: %s : No memory left on device.\n", cmd);
	else if (err_type == IS_DIR)
		printf("minishell: %s : \e[91mIs a directory.\e[0m\n", cmd);
	else if (err_type == INV_ID)
		printf("minishell: %s : \e: not valid in this context: %s\n", cmd, param);
	dupnclose(fd, STDOUT_FILENO);
	return (g_exit_status);
}
//  if (err_type == WCHAR)
// 	ft_putstr_fd("Wrong input character: ", STDERR_FILENO);
// else if (err_type == DUPERR)
// 	ft_putstr_fd("Dup failed", STDERR_FILENO);

// else if (err_type == PIPERR)
// 	ft_putstr_fd("Pipe error", STDERR_FILENO);