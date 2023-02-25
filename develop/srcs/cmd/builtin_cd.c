/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:49:52 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/25 12:49:54 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dest(char *str, t_prompt *prompt)
{
	char	*dest;

	if (ft_strcmp(str, "-") == 0)
	{
		dest = get_env("OLD_PWD", prompt->envp, 7);
		if (!dest)
			return (print_error(OP_NS, "cd", NULL), NULL);
	}
	else
		dest = ft_strdup(str);
	return (dest);
}

int	ft_cd(t_request *request, t_prompt *prompt)
{
	t_token	*token;
	char	*dest;
	char	*dest_bk;

	if (request->nbr_token > 2)
		return (print_error(TM_ARGS, "cd", NULL));
	if (request->nbr_token == 1)
		dest = get_env("HOME", prompt->envp, 4);
	else
		dest = get_dest(request->token->next->str, prompt);
	if (!dest)
		return (g_exit_status);
	dest_bk = ft_strdup(dest);
	g_exit_status = 0;
	update_oldpwd(prompt);
	if (chdir(dest) < 0)
		print_fd_error(dest_bk, "cd", 0);
	free (dest);
	free (dest_bk);
	return (g_exit_status);
}

int	ft_pwd(t_request *request, t_prompt *prompt)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
		return (-1);
}
