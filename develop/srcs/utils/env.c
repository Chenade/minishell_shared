/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 05:59:21 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/25 22:44:35 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (var[0] == '?')
		return (ft_itoa(g_exit_status));
	if (n < 0)
		n = ft_strlen(var);
	while (envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_int(envp[i], '='))
			n2 = ft_strchr_int(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

char	**set_env(char *var, char *value, char **envp, int n)
{
	int		i[2];
	char	*aux[2];

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_int(envp[i[0]], '='))
			i[1] = ft_strchr_int(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			aux[0] = envp[i[0]];
			envp[i[0]] = ft_strdup(aux[1]);
			free(aux[1]);
			free(aux[0]);
			return (envp);
		}
	}
	free(aux[1]);
	return (envp);
}
