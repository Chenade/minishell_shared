#include "minishell.h"

char *rep_line(char *str, int q[3], t_prompt *p)
{
	int i;
	int	len;
	char *tmp;

	i = 0;
	len = get_len_expand_str(str, q, p);
	p->tmp_rep = malloc(sizeof(char) * (len + 1));
	p->tmp_rep[len] = '\0';
	p->tmp_rep = put_str_expand(str, q, p);
	tmp = ft_strdup(p->tmp_rep);
	free(p->tmp_rep);
	p->tmp_rep = NULL;
	return (tmp);
}

char	**expand_cmd(char **aux, t_prompt *p)
{
	int		i;
	int		q[3];
	char	*tmp;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	q[2] = 0;
	while (aux[i])
	{
		tmp = aux[i];
		aux[i] = rep_line(aux[i], q, p);
		// if (p->tmp_rep)
		// 	free(p->tmp_rep);
		free (tmp);
		i++;
	}
	// print_env(aux);
	return (aux);
}