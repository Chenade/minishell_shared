#include "minishell.h"

int	env_key_len(char *out)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (out[++j])
	{
		if (out[j] == ' ' || out[j] == '|' || out[j] == '<' || out[j] == '>'
			|| out[j] == '$' || out[j] == '\'' || out[j] == '"')
			break ;
		len += 1;
	}
	return (len);
}

int	get_malloc_size(char *out, char **envp)
{
	int		i;
	int		j;
	int		single_quote;
	int		malloc_len;
	char	*str;

	i = -1;
	single_quote = 1;
	malloc_len = 0;
	while (out[++i])
	{
		if (out[i] == '\'')
			single_quote *= -1;
		if (out[i] == '$' && single_quote > 0)
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
	int		single_quote;
	char	*val;

	i = -1;
	single_quote = 1;
	nout_i = 0;
	while (out[++i])
	{
		if (out[i] == '\'')
			single_quote *= -1;
		if (out[i] == '$' && single_quote > 0)
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
	new_out = (char *) malloc((malloc_len + 1) * sizeof (char));
	if (!new_out)
	{
		print_error(MEM, NULL, NULL);
		return (NULL);
	}
	new_out[malloc_len] = '\0';
	replace_env(out, new_out, envp);
	free (out);
	return (new_out);
}
