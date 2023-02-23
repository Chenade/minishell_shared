#include "minishell.h"

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
		if (*p == -' ')
			request->nbr_token++;
		else if ((*p == -'>' && *(p + 1) == -'>') || (*p == -'<' && *(p + 1) == -'<'))
			;
		else if (is_sep(*p) && *p != -' ')
			request->nbr_token += 2;
		request->str[i] = *p;
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
		prompt->requests->id = i;
		prompt->requests[i].cmd = NULL;
		prompt->requests[i].token = NULL;
		p++;
		i++;
	}
	i = 0;
	return (0);
}

void	fill_cmd(t_prompt *prompt)
{
	t_token	*tmp;
	int	i;

	i = 0;
	while (i < prompt->nbr_request)
	{
		tmp = prompt->requests[i].token;
		while (tmp)
		{
			// printf("%s:tmp->str\n", tmp->str);
			if (tmp->type == CMD)
				prompt->requests[i].cmd = tmp->str;
			tmp = tmp->next;
			// printf("%s:tmp->str\n", prompt->requests[i].cmd);
		}
		i++;
	}
}

int	fill_request(char *cmd, t_prompt *prompt)
{
	int	i;

	if(init_request(cmd, prompt))
		return (1);
	i = 0;
	while (i < prompt->nbr_request)
	{
		prompt->requests[i].token = fill_token(&(prompt->requests[i]));
		i++;
	}
	fill_cmd(prompt);
	i = 0;
	while (i < prompt->nbr_request)
	{
		print_token(prompt->requests[i].token);
		i++;
	}
	return (0);
}