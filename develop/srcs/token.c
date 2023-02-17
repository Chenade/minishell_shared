#include "minishell.h"

// void	token_exception(t_token *token, t_prompt *p)
// {
// 	while (token->str)
// 	{
// 		if (token->type == OUTPUT)
// 		{
// 			if (!token->prev || token->prev->type == PIPE)
// 			{
// 				if (token->next->next->type == ARG)
// 					token->next->next->type = CMD;
// 			}
// 		}
// 		if (!token->next)
// 			break;
// 		token = token->next;
// 	}
// }

// void	fill_type(t_token *token, int separator, t_prompt *p)
// {
// 	if (!ft_strcmp(token->str, ""))
// 		token->type = EMPTY;
// 	else if (ft_strchr_int(token->str, '>') >= 0 && separator == 0)
// 		token->type = OUTPUT;
// 	else if (!ft_strcmp(token->str, ">>") && separator == 0)
// 		token->type = APPEN;
// 	else if (ft_strchr_int(token->str, '<') >= 0 && separator == 0)
// 		token->type = INPUT;
// 	else if (!ft_strcmp(token->str, "<<") && separator == 0)
// 		token->type = DELIM;
// 	else if (ft_strchr_int(token->str, '|') >= 0 && separator == 0)
// 	{
// 		token->type = PIPE;
// 		p->has_pipe = 1;
// 	}
// 	else if (ft_strchr("-", token->str[0]) && separator == 0)
// 		token->type = OPTN;
// 	else if (ft_strchr_int(token->str, '=') > 0 && separator == 0)
// 		token->type = ENV_DEF;
// 	else if (!token->prev || token->prev->type == PIPE)
// 		token->type = CMD;
// 	else
// 		token->type = ARG;
// }

// t_token	*token_new(char *content)
// {
// 	t_token	*new;
// 	int		size;

// 	if (!content)
// 		return (NULL);
// 	size = ft_strlen(content);
// 	new = (t_token *) malloc (sizeof(t_token));
// 	if (!new)
// 		return (0);
// 	new->type = 0;
// 	if (content && !size)
// 		new->str = ft_strdup("");
// 	else
// 		new->str = content;
// 	new->next = NULL;
// 	return (new);
// }

// t_token	*tokenlast(t_token *token)
// {
// 	if (!token)
// 		return (0);
// 	while (token->next)
// 		token = token->next;
// 	return (token);
// }

// t_token *fill_nodes(char **args)
// {
// 	t_token	*token;
// 	t_token	*tmp;
// 	t_token *prev;
// 	int	i;

// 	i = 1;
// 	token = token_new(args[0]);
// 	if (!token)
// 		return (0);
// 	token->prev = NULL;
// 	while (args[i])
// 	{
// 		tmp = tokenlast(token);
// 		prev = tmp;
// 		tmp->next = token_new(args[i++]);
// 		tmp->next->prev = prev;
// 	}
// 	return (token);
// }


void	set_token_type_sub(t_token *token, int sep)
{
	if (!ft_strcmp(token->str, "&&") && sep)
		token->type = AND;
	else if (!ft_strcmp(token->str, "||") && sep)
		token->type = OR;
	else if (token->prev == NULL || token->prev->type >= PIPE)
		token->type = CMD;
	else if (token->prev->type > DIRE && token->prev->type < PIPE)
		token->type = DIRE;
	else
		token->type = ARG;
}

void	set_token_type(t_token *token, int sep)
{
	if (!ft_strcmp(token->str, ">") && sep)
		token->type = OUTPUT;
	else if (!ft_strcmp(token->str, ">>") && sep)
		token->type = APPEN;
	else if (!ft_strcmp(token->str, "<") && sep)
		token->type = INPUT;
	else if (!ft_strcmp(token->str, "<<") && sep)
		token->type = DELIM;
	else if (!ft_strcmp(token->str, "|") && sep)
		token->type = PIPE;
	else if (ft_strchr_int(token->str, '=') >= 0)
		token->type = ENV_DEF;
	else
		set_token_type_sub(token, sep);
}


t_token	*add_token_new(int type, char *str)
{
	t_token	*ret;

	ret = malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->str = str;
	ret->prev = NULL;
	ret->next = NULL;
	return (ret);
}

void	add_token(t_token **token, char *str, int sep)
{
	t_token	*tmp;

	if (!str)
		return ;
	tmp = *token;
	if (!tmp)
	{
		*token = add_token_new(0, str);
		set_token_type(*token, sep);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_token_new(0, str);
		tmp->next->prev = tmp;
		set_token_type(tmp->next, sep);
	}
}

int	check_empty_token(char *start, char *str, int i, t_prompt *prompt)
{
	char	prev;
	char	next;
printf("**i : %d\n", i);
	prev = *(str - 1);
	next = *(str + 1);
	printf(">>CEHCK_EMPTY_TOKEN\nprec : %c, next : %c\nstr : %s\n", prev, next, str);
	if ((prev == *str) && (start == str - i + 1)
		&& (is_sep(next) || !next))
		add_token(&prompt->token, ft_strdup(""), 0);
	return (1);
}

void	fill_token(t_prompt *prompt, char *str, char *q, int i)
{
	char	*start;

	start = str;
	printf("CMD str:%s\n", str);
	while (*str)
	{
		printf("start : %s, str : %s [i] : %d\n", start, str, i);
		if (!*q && is_quot(*str) && ++i)
			*q = *str;
		else if (*q && (*str == *q) && ++i && check_empty_token(start, str, i, prompt))
			*q = '\0';
		else if (i > 0)
		{
			printf("str - [%s]\n", str);
			*(str - i) = *str;
			printf("AF>str - [%s]\n", str);
		}
		if (!*q && is_sep(*str))
		{
			printf("*****\n");
			add_token(&prompt->token, str_to_token(prompt, start, str - i), 0);
			if (*(str - i) != ' ')
				add_token(&prompt->token, str_to_token(prompt, str - i, str - i + 1), 1);
			start = str - i + 1;
		}
		str++;
	}
	printf("> start : %s, str : %s [i] : %d\n", start, str, i);
	add_token(&prompt->token, str_to_token(prompt, start, str - i), 0);
}