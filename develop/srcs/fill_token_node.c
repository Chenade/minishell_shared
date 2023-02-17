#include "minishell.h"

// char	*end_of_dollar(char *str)
// {
// 	char	*s;

// 	s = validate_key(str + 1, " ");
// 	if (s == str + 1 && ft_isdigit(*s))
// 		return (s + 1);
// 	else if (s == str + 1 && *s == '?')
// 		return (s + 1);
// 	return (s);
// }

int get_env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == '$')
			break;
		else
			i++;
	}
	return (i);
}

int	token_len(t_prompt *prompt, char *str)
{
	int		i;
	int		env_len;
	char	*value;

	i = 0;
	while (*str)
	{
		if (*str == -'$')
		{
			str++;
			env_len = get_env_len(str);
			value = get_env(str, prompt->envp, env_len);
			if (value)
			{
				i += ft_strlen(value);
				free(value);
			}
			str	+= env_len;
			continue ;
		}
		else if (*str == - '<' || *str == - '>')
			i++;
		i++;
		str++;
	}
	return (i);
}

void	str_to_token_sub(t_prompt *prompt, char *str, char *ret)
{
	int		env_len;
	char	*value;
	char	*s;

	while (*str)
	{
		if (*str == - '$')
		{
			str++;
			env_len = get_env_len(str);
			value = get_env(str, prompt->envp, env_len);
			s = value;
			while (s && *s)
				*ret++ = *s++;
			free(value);
			str += env_len;
			if (!*str)
				break ;
		}
		else if (*str == - '>' || *str == - '<'
			|| *str == - '&' || *str == - '|')
		{
			*str = -(*str);
			*ret++ = *str;
		}
		printf("ret[%c]-str[%c]\n", *ret, *str);
		*ret++ = *str++;
	}
	*ret = '\0';
}
 
char	*str_to_token(t_prompt *prompt, char *start, char *end)
{
	char	*ret;
	char	end_tmp;

	printf("------start : %s, end : %s \n", start, end);
	if (start == end)
		return (NULL);
	end_tmp = *end;
	*end = '\0';
	printf("-------------start : %s\n", start);
	ret = (char *)malloc(sizeof(char) * (token_len(prompt, start) + 1));
	if (!ret)
		return (NULL);
	str_to_token_sub(prompt, start, ret);
	printf("REST:[%s]\n", ret);
	*end = end_tmp;
	return (ret);
}