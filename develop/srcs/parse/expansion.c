#include "minishell.h"

int	env_key_len(char *out)
{
	int j;
	int	len;

	j = 0;
	len = 0;
	while (out[++j])
	{
		if (out[j] == ' ' || out[j] == '|' || out[j] == '<' || out[j] == '>' || out[j] == '$' || out[j] == '\'' || out[j] == '"')
			break ;
		len += 1;
	}
	return (len);
}

int malloc_size(char *out, char **envp)
{
	int i;
	int j;
	int	single_quote;
	int malloc_len;

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
			malloc_len += ft_strlen(get_env(out + i + 1, envp, j));
			i += j;
		}
		else
			malloc_len += 1;
	}
	printf("[DEBUG]malloc_len: %d\n", malloc_len);
	return (malloc_len);
}

int	replace_env(char *out, char *new_out)
{
	// int i;
	// int j;
	// int	single_quote;

	// i = -1;
	// single_quote = 1;
	// while (out[++i])
	// {
	// 	if (out[i] == '\'')
	// 		single_quote *= -1;
	// 	if (out[i] == '$' && single_quote > 0)
	// 	{
	// 		j = env_key_len(out + i);
	// 		malloc_len += ft_strlen(get_env(out + i + 1, envp, j));
	// 		i += j;
	// 	}
	// 	else
	// 		malloc_len += 1;
	// }
	return (0);
}

char *expansion(char *out, char **envp)
{
	int		malloc_len;
	char	*new_out;

	malloc_len = malloc_size(out, envp);
	new_out = (char *) malloc((malloc_len + 1) * sizeof (char));
	if (!new_out)
		return (NULL);
	replace_env(out, new_out);
	free (out);
	return (new_out);
}