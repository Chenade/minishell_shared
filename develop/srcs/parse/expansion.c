/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:06:45 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/21 09:06:48 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_key_len(char *out)
{
	int		len;
	char	*tmp;
	int		j;

	j = 0;
	len = 0;
	if (out[j] == '?')
	{
		tmp = ft_itoa(g_exit_status);
		len = ft_strlen(tmp);
		free (tmp);
	}
	else
	{
		while (out[++j])
		{
			if (out[j] == - ' ' || out[j] == - '|' || out[j] == - '<'
				|| out[j] == - '>' || out[j] == '$' || out[j] == '\''
				|| out[j] == '"' || out[j] == ';' || out[j] == '\0')
				break ;
			len += 1;
		}
	}
	return (len);
}

int	get_malloc_size(char *out, char **envp)
{
	int		i;
	int		j;
	t_parse	data;
	int		malloc_len;
	char	*str;

	i = -1;
	malloc_len = 0;
	reset_bool(&data, 1);
	while (out[++i])
	{
		check_quote(&data, out[i]);
		if (out[i] == '$' && data.single_quote > 0)
		{
			j = env_key_len(out + i);
			str = get_env(out + i + 1, envp, j);
			malloc_len += ft_strlen(str);
			free (str);
			i += j;
		}
		else
			malloc_len += 1;
	}
	return (malloc_len);
}

int	insert_str(char *new_out, int *nout_i, char *str, int len)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (++i < len)
	{
		new_out[*nout_i] = str[i];
		*nout_i += 1;
	}
	return (0);
}

int	replace_env(char *out, char *new_out, char **envp)
{
	int		i;
	int		j;
	int		nout_i;
	t_parse	data;
	char	*val;

	i = -1;
	nout_i = 0;
	reset_bool(&data, 1);
	while (out[++i])
	{
		check_quote(&data, out[i]);
		if (out[i] == '$' && data.single_quote > 0)
		{
			j = env_key_len(out + i);
			val = get_env(out + i + 1, envp, j);
			insert_str (new_out, &nout_i, val, ft_strlen(val));
			free (val);
			i += j;
		}
		else
			insert_str (new_out, &nout_i, &out[i], 1);
	}
	return (0);
}

char	*expansion(char *out, char **envp)
{
	int		malloc_len;
	char	*new_out;

	malloc_len = get_malloc_size(out, envp);
	if (malloc_len == 0 )
		return (NULL);
	if (malloc_len)
		new_out = (char *) malloc((malloc_len + 1) * sizeof (char));
	if (!new_out)
		return (print_error(MEM, NULL, NULL), NULL);
	new_out[malloc_len] = '\0';
	replace_env(out, new_out, envp);
	free (out);
	return (new_out);
}
	// printf("[DEBUG] [%s]\n", new_out);
