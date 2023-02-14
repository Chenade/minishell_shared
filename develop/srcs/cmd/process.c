#include "minishell.h"

t_token	*move_to(t_token *pre, int index)
{
	int		i;
	t_token	*token;
	
	i = 0;
	token = pre;
	while (token)
	{
		if (i == index)
			break ;
		i += 1;
		if (!token->next)
			break ;
		token = token->next;
	}
    return (token);
}
//  execve(const char *pathname, char *const argv[], char *const envp[]);
int	builtin_cmd(char *cmd, int i, t_prompt *prompt)
{
	int		result;

	result = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		result = ft_echo(i + 1, prompt);
	else if (ft_strcmp(cmd, "cd") == 0)
		result = ft_cd(i + 1, prompt);
	else if (ft_strcmp(cmd, "pwd") == 0)
		result = ft_pwd(prompt);
	else if (ft_strcmp(cmd, "export") == 0)
		result = ft_export(i + 1, prompt);
	else if (ft_strcmp(cmd, "unset") == 0)
		result = ft_unset(i + 1, prompt);
	else if (ft_strcmp(cmd, "env") == 0)
	{
		print_env(prompt->envp);
		result = 0;
	}
	else
	{
		char *argv[] = {"ls", "-la", NULL};
		// result =  execve("/usr/bin/ls", argv, prompt->envp);
		// printf("[DEBUG] %d\n", result);
		char *ac[] = {"cat", "Makefile", NULL};
		int tmp = execve("/usr/bin/cat", argv, prompt->envp);
		printf("[DEBUG] %d\n", tmp);
		// exec_bin(cmd, prompt);
	}
	return (result);
}

int			error_message_fd(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (fd == -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	if (folder)
		closedir(folder);
	close(fd);
	g_sig.exit_status = 1;
	return (1);
}

int	ft_open(int type, char *path)
{
	int	fd;

	if (type == 7)
		fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	else if (type == 9)
		fd = open(path, O_WRONLY|O_CREAT|O_APPEND, 0666);
	else if (type == 6)
		fd = open(path, O_RDONLY, 0666);
	else if (type == 8)
		fd = open(path, O_RDONLY, 0666);
	return (fd);
}

int redirect_output(t_prompt *prompt)
{
	t_token	*token;
	
    token = prompt->token;
	while (token)
	{
		if (token->type == 7 || token->type == 9)
		{
			if (token->next && token->next->type == 2)
			{
				if (prompt->output_fd != 0)
					close(prompt->output_fd);
				prompt->output_fd = ft_open(token->type, token->next->str);
				if (prompt->output_fd < 0)
					return (error_message_fd(token->next->str));
			}
			else
   				return (print_error(SYNERR, "", token->str));
		}
		if (!token->next)
			break;
		token = token->next;
	}
    return (0);
}

int redirect_input(t_prompt *prompt)
{
	t_token	*token;
	
    token = prompt->token;
	while (token)
	{
		if (token->type == 6 || token->type == 8)
		{
			if (token->next && token->next->type == 2)
			{
				if (prompt->input_fd != 0)
					close(prompt->input_fd);
				prompt->input_fd = ft_open(token->type, token->next->str);
				if (prompt->input_fd < 0)
					return (error_message_fd(token->next->str));
			}
			else
   				return (print_error(SYNERR, "", token->str));
		}
		if (!token->next)
			break;
		token = token->next;
	}
    return (0);
}


int process(t_prompt *prompt)
{
    int		status;
	int		i;
	t_token	*token;
	
	status = 0;
	i = 0;
	prompt->output_fd = 0;
	prompt->input_fd = 0;
    token = prompt->token;
	prompt->result = NULL;
	print_token(token);

	redirect_output(prompt);
	if (g_sig.exit_status)
		return (g_sig.exit_status);
	
	redirect_input(prompt);
	if (g_sig.exit_status)
		return (g_sig.exit_status);
	
	while (token && !status)
	{
		if (token->type == 1)
			status = builtin_cmd(token->str, i, prompt);
		if (!token->next)
			break;
		token = token->next;
		i += 1;
	}
	printf("[DEBUG] status: %d\n", status);
    return (status);
}