#include "minishell.h"

char	*expand_env(char *str, int *i, int *len, t_prompt *p)
{
	int	env_len;
	int	env_count;
	char *tmp;
	int	j;

	j = 0;
	env_len = get_env_len(str + *i + 1);
	tmp = get_env(str + *i + 1, p->envp, env_len);
	if (tmp)
	{
		while (tmp[j])
		{
			p->tmp_rep[*len] = tmp[j];
			(*len)++;
			j++;
		}
		free (tmp);		
	}
	*i += env_len + 1;
	return (p->tmp_rep);
}

char *get_norm_expand(char *str, t_prompt *p, int i[2])
{
	// printf("str : %s\n", str);
	while (str[i[0]])
	{
		if (str[i[0]] == '$')
		{
			p->tmp_rep = expand_env(str, &i[0], &i[1], p);
			continue;
		}
		else
		{
			p->tmp_rep[i[1]] = str[i[0]];
			i[1]++;
		}
		i[0]++;
	}
	return (p->tmp_rep);
}

char *get_double_expand(char *str, int q[3], t_prompt *p, int i[2])
{

	while (str[i[0]])
	{
		q[1] = (q[1] + (!q[0] && q[2] % 2 == 0 && str[i[0]] == '\"'));
		if (!q[0] && q[1])
		{
			q[2] = (q[2] + ((q[1] % 2 == 0) && str[i[0]] == '\'')) % 2;
			if (q[1] % 2 != 0)
			{
				if (str[i[0]] == '$')
				{
					p->tmp_rep = expand_env(str, &i[0], &i[1], p);
					continue;
				}
				else if (str[i[0]] != '\"')
					p->tmp_rep[i[1]++] = str[i[0]];
			}
			else if (q[1] % 2 == 0)
			{
				if (!q[2] && str[i[0]] == '$')
				{
					p->tmp_rep = expand_env(str, &i[0], &i[1], p);
					continue;
				}
				else if ((!q[2] && str[i[0]] != '\"' && str[i[0]] != '\'')
					|| (q[2] && str[i[0]] != '\''))
					p->tmp_rep[i[1]++] = str[i[0]];
			}
		}
		else if (!q[1])
			p->tmp_rep[i[1]++] = str[i[0]];
		i[0]++;
	}
	return (p->tmp_rep);
}

char *get_single_expand(char *str, int q[3], t_prompt *p, int i[2])
{

	while(str[i[0]])
	{
		q[0] = (q[0] + (!q[1] && str[i[0]] == '\''));
		if (q[0] && !q[1])
		{
			q[2] = (q[2] + (!q[1] && str[i[0]] == '\"')) % 2;
			if ((q[0] % 2) != 0)
			{
				if (str[i[0]] != '\'')
				{
					p->tmp_rep[i[1]++] = str[i[0]];
				}
			}
			else if (q[0] % 2 == 0)
			{
				if (str[i[0]] == '$')
				{
					p->tmp_rep = expand_env(str, &i[0], &i[1], p);
					continue;
				}
				if ((str[i[0]] != '\'' && str[i[0]] != '\"')) //q[2] && 
					p->tmp_rep[i[1]++] = str[i[0]];
			}
		}
		else if (!q[0])
			p->tmp_rep[i[1]++] = str[i[0]];
		i[0]++;
	}
	return (p->tmp_rep);
}

char *put_str_expand(char *str, int q[3], t_prompt *p)
{
	int	tmp[3];

	tmp[0] = 0;
	tmp[1] = 0;
	q[2] = 0;
	if (q[0] && !q[1])
	{
		q[0] = 0;
		return (get_single_expand(str, q, p, tmp));
	}
	else if (!q[0] && q[1])
	{
		q[1] = 0;
		return (get_double_expand(str, q, p, tmp));
	}
	else if (!q[0] && !q[1])
	{
		return (get_norm_expand(str, p, tmp));
	}
}
