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

#define READEND 0
#define WRITEEND 1

int			magic_box2(char *path, t_request *request, char *env, t_prompt *prompt)
{
	int		ret;
	int		tmp;

	request->pid = fork();
	pipe(prompt->pipefd);
	if (request->pid == 0)
	{
		close(prompt->pipefd[READEND]);
		if (prompt->prev_pipefd[READEND] != -1)
		{
			dup2(prompt->prev_pipefd[READEND], STDIN_FILENO);
			ft_close(prompt->prev_pipefd[READEND]);
		}
		if (request->nbr_token != 2)
		{
			dup2(prompt->pipefd[WRITEEND], STDOUT_FILENO);
			ft_close(prompt->pipefd[WRITEEND]);
		}
		if (path && ft_strchr(path, '/') != NULL)
			tmp = execve(path, request->tab, prompt->envp);
		ret = error_message(path, request->cmd);
		exit(ret);
	}
	else
	{
		close(prompt->pipefd[WRITEEND]);
		ft_close(prompt->prev_pipefd[READEND]);
		ft_close(prompt->prev_pipefd[WRITEEND]);
		prompt->prev_pipefd[READEND] = prompt->pipefd[READEND];
		prompt->prev_pipefd[WRITEEND] = prompt->pipefd[WRITEEND];
	}
	return (0);
}

int			magic_box(char *path, t_request *request, char *env, t_prompt *prompt)
{
	char	*ptr;
	int		ret;
	int tmp;

	ret = 0;
	request->pid = fork();
	
	if (request->pid == 0)
	// if (pid == 0) 
	// {
    //     // Child process - set up stdout to write to pipe
    //     if (request->pipout_fd != -1) {
    //         ft_close(request->pipout_fd);
    //     }
    //     if (request->output_fd != -1) {
    //         ft_close(request->input_fd);
    //         dup2(request->output_fd, STDOUT_FILENO);
    //         ft_close(request->output_fd);
    //     }

    //     // Execute the command
    //     if (path && ft_strchr(path, '/') != NULL)
	// 		tmp = execve(path, request->tab, prompt->envp);
	// 	ret = error_message(path, request->cmd);
	// 	exit(ret);
    // } else {
    //     // Parent process - set up stdin to read from pipe
    //     if (request->pipout_fd != -1) {
    //         ft_close(request->pipout_fd);
    //     }
    //     if (request->output_fd != -1) {
    //         ft_close(request->output_fd);
    //         dup2(request->input_fd, STDIN_FILENO);
    //         ft_close(request->input_fd);
    //     }
    // }


	{
		fprintf(stderr, "[DEBUG] pipout_fd = %d, input_fd = %d, output_fd = %d\n", request->pipout_fd, request->input_fd, request->output_fd);

		if (request->pipout_fd != -1)
			close(request->pipout_fd);
		if (dup2(request->input_fd, 0) < 0)
			return (perror(path), 1);
		if (dup2(request->output_fd, 1) < 0)
			return (perror("dup2-2"), 1);
		fprintf(stderr, "[DEBUG ft_close 75]cmd: %s,  fd: %d\n",request->cmd, request->output_fd);
		// ft_close(request->input_fd);
		// ft_close(request->output_fd);
		if (path && ft_strchr(path, '/') != NULL)
			tmp = execve(path, request->tab, prompt->envp);
		ret = error_message(path, request->cmd);
		exit(ret);
	}
	else
	{
		// close i in the parent always
		// close prevpipe if its not at -1
		// copy into the prev the fd[0] (prev_pipe = fd[0])
		
		// ft_close(request->pipout_fd);
		// fprintf(stderr, "[DEBUG ft_close 89]cmd: %s,  fd: %d\n",request->cmd, request->input_fd);
		ft_close(request->input_fd);
		// fprintf(stderr, "[DEBUG ft_close 91]cmd: %s,  fd: %d\n",request->cmd, request->output_fd);
		if (request->pipout_fd != -1)
			ft_close(request->output_fd);
		int status;
        // if (waitpid(request->pid, &status, 0) == -1) {
        //     perror("waitpid");
        //     exit(EXIT_FAILURE);
        // }
		// if (WIFEXITED(status)) {
		// 	fprintf(stderr, "[DEBUG] child exited, status=%d\n", WEXITSTATUS(status));
		// } else if (WIFSIGNALED(status)) {
		// 	fprintf(stderr, "[DEBUG] child killed (signal %d)\n", WTERMSIG(status));
		// } else if (WIFSTOPPED(status)) {
		// 	fprintf(stderr, "[DEBUG] child stopped (signal %d)\n", WSTOPSIG(status));
		// }
		// waitpid(pid, &ret, 0);
	}
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
		while (request->cmd && bin[i] && path == NULL)
			path = check_dir(bin[i++], request->cmd);
		free_pp(bin);
	}
	if (!env || path == NULL)
		path = ft_strdup(request->cmd);
	ret = magic_box2(path, request, env, prompt);
	free(path);
	free(env);
	return (ret);
}
