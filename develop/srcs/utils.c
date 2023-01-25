#include "minishell.h"

int	ft_strchr_int(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

void	free_pp(char **pp)
{
	int		i;

    i = 0;
	if (pp == NULL)
		return ;
	while (pp[i])
		free(pp[i++]);
	free(pp);
}

void	free_matrix(char ***m)
{
	int	i;

	i = 0;
	while (m && m[0] && m[0][i])
	{
		free(m[0][i]);
		i++;
	}
	if (m)
	{
		free(m[0]);
		*m = NULL;
	}
}

/* Add new str to end of matrix */
// char	**extend_matrix(char **in, char *newstr)
// {
// 	char	**out;
// 	int		len;
// 	int		i;

// 	i = -1;
// 	out = NULL;
// 	if (!newstr)
// 		return (in);
// 	len = get_matrixlen(in);
// 	out = malloc(sizeof(char *) * (len + 2));
// 	if (!out)
// 		return (in);
// 	out[len + 1] = NULL;
// 	while (++i < len)
// 	{
// 		out[i] = ft_strdup(in[i]);
// 		if (!out[i])
// 		{
// 			free_matrix(&in);
// 			free_matrix(&out);
// 		}
// 	}
// 	out[i] = ft_strdup(newstr);
// 	free_matrix(&in);
// 	return (out);
// }

int	get_matrixlen(char **m)
{
	int	i;

	i = 0;
	while (m && m[i])
		i++;
	return (i);
}

char	**ft_dup_matrix(char **m)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	n_rows = get_matrixlen(m);
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	while (m[i])
	{
		out[i] = ft_strdup(m[i]);
		if (!out[i])
		{
			free_matrix(&out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}