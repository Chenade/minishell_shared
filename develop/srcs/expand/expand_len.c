#include "minishell.h"

int manage_double_q(char *str, int q[3], t_prompt *p, int i[2])
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
					i[0] += jump_env(str, i[0], &i[1], p);
					continue;
				}
				else if (str[i[0]] != '\"')
					i[1]++;
			}
			else if (q[1] % 2 == 0)
			{
				if (!q[2] && str[i[0]] == '$')
				{
					i[0] += jump_env(str, i[0], &i[1], p);
					continue;
				}
				else if ((!q[2] && str[i[0]] != '\"' && str[i[0]] != '\'')
					|| (q[2] && str[i[0]] != '\''))
					i[1]++;
			}
		}
		else if (!q[1])
			i[1]++;
		i[0]++;
	}
	return (i[1]);
}
// ERROR CASE :  echo '""'$SHLVL'""'
// ERROR CASE :  echo '"'$SHLVL'"'
int	manage_single_q(char *str, int q[3], t_prompt *p, int i[2])
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
					i[1]++;
			}
			else if (q[0] % 2 == 0)
			{
				if (str[i[0]] == '$')
				{
					i[0] += jump_env(str, i[0], &i[1], p);
					continue;
				}
				if (str[i[0]] != '\'' && str[i[0]] != '\"') //q[2] && 
					i[1]++;
			}
		}
		else if (!q[0])
			i[1]++;
		i[0]++;
	}
	return (i[1]);
}

int	manage_norm(char *str, t_prompt *p)
{
	int i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i += jump_env(str, i, &len, p);
			continue;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	get_len_expand_str(char *str, int q[3], t_prompt *p)
{
	int	i;
	int	tmp[2];

	i = 0;
	tmp[0] = 0;
	tmp[1] = 0;
	while (str[i] && (!q[0] && !q[1]))
	{
		q[0] = (q[0] + (!q[1] && str[i] == '\''));
		q[1] = (q[1] + (!q[0] && str[i] == '\"'));
		i++;
	}
	if (q[0] && !q[1])
	{
		q[0] = 0;
		return (manage_single_q(str, q, p, tmp));
	}
	else if (!q[0] && q[1])
	{
		q[1] = 0;
		return (manage_double_q(str, q, p, tmp));
	}
	else if (!q[0] && !q[1])
		return (manage_norm(str, p));
}
