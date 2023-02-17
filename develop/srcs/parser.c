#include "minishell.h"

extern int	exit_status;

// void	*parse_args(char **args, t_prompt *p)
// {
// 	t_token	*tmp;
// 	int		i;

// 	p->token = fill_nodes(args);
// 	if (!p->token)
// 		return (p);
// 	tmp = p->token;
// 	while (tmp->str)
// 	{
// 		fill_type(tmp, 0, p);
// 		if (!tmp->next)
// 			break;
// 		tmp = tmp->next;
// 	}
// 	tmp = p->token;
// 	token_exception(tmp, p);
// 	exit_status = process(p);
// 	i = token_countcmd(p->token);
// 	while (i--)
// 		waitpid(-1, &exit_status, 0); 		//waiting any child process
// 	return (p);
// }

// char	**ft_fill_array(char **aux, char const *cmd, char *set, int i[3])
// {
// 	int		len;
// 	int		q[2];

// 	q[0] = 0;
// 	q[1] = 0;
// 	len = ft_strlen(cmd);
// 	while (cmd[i[0]])
// 	{
// 		while (ft_strchr(set, cmd[i[0]]) && cmd[i[0]] != '\0')
// 			i[0]++;
// 		i[1] = i[0];
// 		while ((!ft_strchr(set, cmd[i[0]]) || q[0] || q[1]) && cmd[i[0]])
// 		{
// 			q[0] = (q[0] + (!q[1] && cmd[i[0]] == '\'')) % 2;
// 			q[1] = (q[1] + (!q[0] && cmd[i[0]] == '\"')) % 2;
// 			i[0]++;
// 		}
// 		if (i[1] >= len)
// 			aux[i[2]++] = "\0";
// 		else
// 			aux[i[2]++] = ft_substr(cmd, i[1], i[0] - i[1]);
// 	}
// 	return (aux);
// }

//     // q[0] = quote
//     // q[1] = sin_doub
// int ft_count_words(const char *cmd, int q[2])
// {
//     int i = 0;
//     int count = 0;

//     while (cmd[i])
//     {
//         if (cmd[i] != ' ')
//         {
//             count++;
// 			while (cmd[i] && (cmd[i] != ' ' || q[0]))
// 			{
// 				if (!q[0] && (!q[0] && (cmd[i] == ';' || cmd[i] == '\\')))
// 					return (-2);
// 				if (!q[1] && (cmd[i] && (cmd[i] == '\"' || cmd[i] == '\'')))
// 						q[1] = cmd[i];
// 				q[0] = (q[0] + (cmd[i] == q[1])) % 2;
// 				q[1] *= (q[0] != 0);
// 				i++;
// 			}
// 			if (q[0])
// 				return (-1);
// 		}
//         else
//             i++;
//     }
//     return (count);
// }

// char	**ft_cmdtrim(char const *cmd, char *set)
// {
// 	char	**aux;
// 	int		nwords;
// 	int		i[3];
// 	int		q[2];

// 	i[0] = 0;
// 	i[1] = 0;
// 	i[2] = 0;
// 	q[0] = 0;
// 	q[1] = 0;
// 	if (!cmd)
// 		return (NULL);
// 	nwords = ft_count_words(cmd, q);
// 	if (nwords == -1)
// 	{
// 		print_error(QUOTE, (char *)cmd, NULL);
// 		return (NULL);
// 	}
// 	aux = malloc((nwords + 1) * sizeof(char *));
// 	if (aux == NULL)
// 		return (NULL);
// 	aux = ft_fill_array(aux, cmd, set, i);
// 	aux[nwords] = NULL;
// 	return (aux);
// }

int	dollar_check(char *str)
{
	if (*str == '$' && (ft_isalnum(*(str + 1)) || *(str + 1) == '_'))
		return (1);
	if (*str == '$' && *(str + 1) == '?')
		return (1);
	return (0);
}

int	sep_check(char *str)
{
	while (*str == ' ')
		str++;
	if (is_sep(*str) || !*str)
		return (1);
	return (0);
}

int	trim_space_sub(char **pstr, char *quot, int *i)
{
	char	*s;

	s = *pstr;
	if (!*quot && *s == ' ')
	{
		if (!(is_sep(*(s - 1)) || sep_check(s)))
		{
			*(s - *i) = *s;
			s++;
		}
		while (*s == ' ' && ++(*i))
			s++;
		*pstr = s;
		return (1);
	}
	else if (!*quot && (*s == '>' && *(s + 1) == '|'))
	{
		*(s - *i) = *s;
		(*pstr) += 2;
		*i += 1;
		return (1);
	}
	return (0);
}

void	replace_char(char **pstr, char *quot, int *i)
{
	char	*s;

	s = *pstr;
	if (*quot != '\'' && dollar_check(s))
		*s = -(*s);
	else if (*quot)
		return ;
	else if ((*s == '<' && *(s + 1) == '<')
		|| (*s == '>' && *(s + 1) == '>')
		|| (*s == '&' && *(s + 1) == '&')
		|| (*s == '|' && *(s + 1) == '|'))
	{
		*(s + 1) = -(*(s + 1));
		(*pstr)++;
		*i += 1;
	}
}

void	cmdtrim(char *str, char *q, int i)
{
	while (*str == ' ' && ++i)
		str++;
	while (*str)
	{
		replace_char(&str, q, &i);
		if (!*q && is_quot(*str))
			*q = *str;
		else if (*str == *q)
			*q = '\0';
		else if (trim_space_sub(&str, q, &i))
			continue ;
		*(str - i) = *str;
		str++;
	}
	*(str - i) = '\0';
}

int	check_args(char *out, t_prompt *prompt)
{
	char	q;
	int		i;

	if (out && *out)
		add_history(out);
	q = '\0';
	i = 0;
	cmdtrim(out, &q, i);
	if (q)
	{
		exit_status = 258;
		print_error(QUOTE, (char *)out, NULL);
		return (0);
	}
	fill_token(prompt, out, &q, i);
	if (!prompt->token)
		return (0);
	return (1);
}
