#include "minishell.h"

int	error_message(char *path, char *cmd)
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
	return (-1);
}

int			magic_box(char *path, char **tab, char *env, t_prompt *prompt)
{
	char	*ptr;
	int		ret;
	int tmp;

	ret = 0;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		if (path && ft_strchr(path, '/') != NULL)
			tmp = execve(path, tab, prompt->envp);
		ret = error_message(path, tab[0]);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	if (ret == 32256 || ret == 32512)
		return (ret / 256);
	else
		return (!!ret);
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

char	*check_path(char *cmd, char *env)
{
	int		i;
	char	**bin;
	char	*path;

	i = 0;
	path = NULL;
	if (env)
	{
		bin = ft_split(env, ':');
		if (!bin[0])
			return (NULL);
		i = 0;
		while (cmd && bin[i] && path == NULL)
			path = check_dir(bin[i++], cmd);
		free_pp(bin);
		return (path);
	}
	return (cmd);
}

int	exec_bin(t_request *request, t_prompt *prompt)
{
	int		i;
	char	**bin;
	char	*path;
	char	*env;
	int		ret;

	i = 0;
	ret = 0;
	env = get_env("PATH", prompt->envp, -1);
	path = NULL;
	if (env)
	{
		bin = ft_split(env, ':');
		if (!bin[0])
			return (-1);
		i = 0;
		while (request->cmd 
		&& bin[i]
		 && path == NULL)
			path = check_dir(bin[i++], request->cmd);
		free_pp(bin);
	}
	if (!env || path == NULL)
		path = request->cmd;
	ret = magic_box(path, request->tab, env, prompt);
	free(path);
	free(env);
	return (ret);
}
