#include "minishell.h"

void	fill_type(t_token *token, int separator)
{
	if (!ft_strcmp(token->str, ""))
		token->type = EMPTY;
	else if (!ft_strcmp(token->str, ">") && separator == 0)
		token->type = OUTPUT;
	else if (!ft_strcmp(token->str, ">>") && separator == 0)
		token->type = APPEN;
	else if (!ft_strcmp(token->str, "<") && separator == 0)
		token->type = INPUT;
	else if (!ft_strcmp(token->str, "<<") && separator == 0)
		token->type = DELIM;
	else if (ft_strchr("-", token->str[0]) && separator == 0)
		token->type = OPTN;
	else if (ft_strchr_int(token->str, '=') > 0 && separator == 0)
		token->type = ENV_DEF;
	else if (!token->prev || )
		token->type = CMD;
	else if (token->type != ENV_VAL)
		token->type = ARG;
}

t_token	*tokenlast(t_token *token)
{
	if (!token)
		return (0);
	while (token->next)
		token = token->next;
	return (token);
}

char *set_str(t_token *new, char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (is_sep(str[i]))
			str[i] *= -1;
		new->str[i] = str[i];
		i++;
	}
	new->str[i] = '\0';
	return (new->str);
}

t_token	*add_node_end(t_token *token, char *str, int len)
{
	t_token	*tmp;
	t_token *end;
	t_token	*new;
	
	if (!token || !str)
		return (NULL);
	tmp = NULL;
	end = token;
	end = tokenlast(end);
	if (!token->next && !token->str)
		new = token;
	else
	{
		tmp = end;
		new = (t_token *) malloc (sizeof(t_token));
	}
	new->str = (char *)malloc(sizeof(char) * (len + 1));
	new->str = set_str(new, str,len);
	new->prev = tmp;
	end->next = new;
	new->next = NULL;
	fill_type(tokenlast(token), 0);
	return (token);
}

t_token	*token_create(void)
{
	t_token	*new;

	new = (t_token *) malloc (sizeof(t_token));
	if (!new)
		return (0);
	new->str = NULL;
	new->next = NULL;
	new->prev = NULL;
}

t_token	*fill_token(t_request *request)
{
	int	i;
	int	len;
	char *p;
	t_token *token;

	token = token_create();
	p = request->str;
	i = -1;
	while (*(p) != '\0' && ++i < request->nbr_token)
	{
		len = 0;
		while(p[len] && !is_sep(p[len]))
			len++;
		if (is_sep(p[len]) || !p[len])
		{
			if (len)
				token = add_node_end(token, p, len);
			else if(!len && p[len] != -' ')
				token = add_node_end(token, p, ++len);
			if (p[len] == -' ')
				len++;
		}
		p += len;
	}
	return (token);
}

int	set_request(char *p, t_request *request)
{
	int	i;

	i = 0;
	request->str_len = 0;
	request->nbr_token = 1;
	while (p[i] && p[i] != -'|')
		i++;
	request->str_len = i;
	request->str = (char *)malloc(sizeof(char) * (request->str_len + 1));
	if (!request->str)
		return (print_error(MEM, NULL, NULL));
	i = 0;
	while (*p && *p != -'|')
	{
		request->str[i] = *p;
		if (*p == -' ')
			request->nbr_token++;
		else if (is_sep(*p) && *p != -' ')
			request->nbr_token += 2;
		i++;
		p++;
	}
	request->str[i] = '\0';
	return (0);
}

int	init_request(char *cmd, t_prompt *prompt)
{
	int	i;
	int j;
	char *p;

	i = 0;
	p = cmd;
	prompt->clean = cmd;
	prompt->requests = (t_request *) malloc(sizeof(t_request) * prompt->nbr_request);
	if (!prompt->requests)
		return (print_error(MEM, NULL, NULL));
	while (i < prompt->nbr_request)
	{
		if (set_request(p, &(prompt->requests[i])))
			return (1);
		p += prompt->requests[i].str_len;
		p++;
		i++;
	}
	i = 0;
	return (0);
}

int	fill_request(char *cmd, t_prompt *prompt)
{
	int	i;

	// printf("nbr_request : %d\n", prompt->nbr_request);
	if(init_request(cmd, prompt))
		return (1);
	i = 0;
	while (i < prompt->nbr_request)
	{
		prompt->requests[i].token = fill_token(&(prompt->requests[i]));
		i++;
	}
	i=0;
	while (i < prompt->nbr_request)
		print_token(prompt->requests[i++].token);
}