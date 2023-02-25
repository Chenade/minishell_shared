/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:09:15 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/21 09:09:17 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call_execve(char *path, t_request *request, t_prompt *prompt)
{
	int	tmp;
	int	ret;

	if (path && ft_strchr(path, '/') != NULL)
		tmp = execve(path, request->tab, prompt->envp);
	ret = print_fd_error(path, request->cmd, 1);
	g_exit_status = 127;
	ret = 127;
	return (ret);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;
	char			*tmp;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strcmp(item->d_name, command) == 0)
		{
			tmp = ft_strjoin(bin, "/");
			path = ft_strjoin(tmp, item->d_name);
			free (tmp);
		}
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

int	exec_bin(t_request *request, t_prompt *prompt)
{
	int		i;
	char	**bin;
	char	*path;
	char	*env;
	int		ret;

	ret = 0;
	env = get_env("PATH", prompt->envp, -1);
	path = NULL;
	if (env)
	{
		bin = ft_split(env, ':');
		if (!bin[0])
			return (-1);
		i = 0;
		while (request->cmd && bin[i] && path == NULL)
			path = check_dir(bin[i++], request->cmd);
		free_pp(bin);
	}
	if (!env || path == NULL)
		path = ft_strdup(request->cmd);
	free(env);
	ret = call_execve(path, request, prompt);
	free(path);
	return (ret);
}
