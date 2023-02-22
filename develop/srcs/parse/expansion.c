#include "minishell.h"

int	env_key_len(char *out)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (out[++j])
	{
		if (out[j] == -' ' || out[j] == -'|' || out[j] == -'<' || out[j] == -'>'
			|| out[j] == '$' || out[j] == '\'' || out[j] == '\"' || out[j] == '\0'
			|| out[j] == ' ')
			break ;
		len += 1;
	}
	return (len);
}

int	get_malloc_size(char *out, char **envp, int q[2])
{
	int		i;
	int		j;
	int		malloc_len;
	char	*str;

	i = -1;
	malloc_len = 0;
	while (*out == ' ')
		out++;
	while (out[++i])
	{
		q[0] = (q[0] + (!q[1] && out[i] == '\'')) % 2;
		q[1] = (q[1] + (!q[0] && out[i] == '\"')) % 2;
		if (out[i] =='$' && out[i + 1] == '?' && !q[0] && i++)
			malloc_len += exit_strlen();
		else if (out[i] == '$' && !q[0])
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

int	replace_env(char *out, char *new_out, char **envp, int q[2])
{
	int		i;
	int		j;
	int		nout_i;
	char	*val;

	i = -1;
	nout_i = 0;
	while (out[++i])
	{
		q[0] = (q[0] + (!q[1] && out[i] == '\'')) % 2;
		q[1] = (q[1] + (!q[0] && out[i] == '\"')) % 2;
		if (out[i] =='$' && out[i + 1] == '?' && !q[0] && i++)
			nout_i = expand_exit(new_out, nout_i);
		else if (out[i] == '$' && !q[0])
		{
			j = env_key_len(out + i);
			val = get_env(out + i + 1, envp, j);
			insert_str (new_out, &nout_i, val, ft_strlen(val));
			free (val);
			i += j;
		}
		// else if (out[i] == -'$')
		// 	out[i] = '$';
		else
			insert_str (new_out, &nout_i, &out[i], 1);
	}
	return (0);
}

char	*expansion(char *out, char **envp)
{
	int		malloc_len;
	int		q[2];
	char	*new_out;

	q[0] = 0;
	q[1] = 0;
	malloc_len = get_malloc_size(out, envp, q);
	if (malloc_len)
		new_out = (char *) malloc((malloc_len + 1) * sizeof (char));
	if (malloc_len == 0 || !new_out)
		return (NULL);
	new_out[malloc_len] = '\0';
	replace_env(out, new_out, envp, q);
	free (out);
	// printf("[DEBUG] [%s]\n", new_out);
	return (new_out);
}
