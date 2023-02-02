#include "minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int			error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = -1; //UNKNOWN_COMMAND;
	else
		ret = -1; //IS_DIRECTORY;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int			magic_box(char *path, char *cmd, char *env, t_prompt *prompt)
{
	char	argv[2][9] = {"cat", "Makefile"};
	char	*ptr;
	int		ret;

	ret = 0;
	printf("[DEBUG] %s\n", path);
	printf("[DEBUG] %s\n", argv[0]);
	printf("[DEBUG] %s\n", argv[1]);
	// printf("[DEBUG] %s", ft_strchr("path", '/'));
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		// if (ft_strchr(path, '/') != NULL)
			int tmp = execve(path, argv, prompt->envp);
			printf("[DEBUG] %d\n", tmp);
		// else
			// printf("[DEBUG] %s", ft_strchr("path", '/'));

		// ret = error_message(path);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	ret = (ret == 32256 || ret == 32512) ? ret / 256 : !!ret;
	return (ret);
}

char		*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free (tmp);
	return (path);
}

char		*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, command) == 0)
			path = path_join(bin, item->d_name);
	}
	closedir(folder);
	return (path);
}

int			exec_bin(char *cmd, t_prompt *prompt)
{
	int		i;
	char	**bin;
	char	*path;
    char    *env;
	int		ret;

	i = 0;
	ret = 0;
    path = NULL;
    env = get_env("PATH", prompt->envp, 3);
	bin = ft_split(env, ':');
	if (!bin[0])
		return (-1);
	i = 0;
	while (cmd && bin[i] && path == NULL)
		path = check_dir(bin[i++], cmd);
	// if (path != NULL)
		ret = magic_box(path, cmd, env, prompt);
	// else    
	// 	ret = magic_box(args[0], args, env, mini);
	free_pp(bin);
	free(path);
	return (ret);
}