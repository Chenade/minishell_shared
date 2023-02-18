#include "minishell.h"

int	process_request(char *str, t_request *request)
{
	int		i;
	t_parse	data;

	i = -1;
	request->str = ft_strtrim(str, " ");
	if (!request->str)
		return (print_error(MEM, NULL, NULL));
	reset_bool(&data, 1);
	while (request->str[++i])
	{
		check_quote(&data, request->str[i]);
		if (request->str[i] == '|'
			&& data.single_quote > 0 && data.double_quote > 0)
			break ;
	}
	request->str[i] = '\0';
	str = ft_strtrim(request->str, " ");
	if (!str)
		return (print_error(MEM, NULL, NULL));
	free (request->str);
	request->str = str;
	request->str_len = ft_strlen(str);
	return (0);
}

int	set_request(t_prompt *prompt)
{
	int		i;
	int		t;
	t_parse	data;

	i = -1;
	t = 1;
	reset_bool(&data, 1);
	if (process_request(prompt->clean, &prompt->requests[0]))
		return (1);
	while (prompt->clean[++i])
	{
		check_quote(&data, prompt->clean[i]);
		if (prompt->clean[i] == '|'
			&& data.single_quote > 0 && data.double_quote > 0)
		{
			if (process_request(prompt->clean + i + 1, &prompt->requests[t]))
			return (1);
			t += 1;
		}
	}
	return (0);
}

int	count_pipe(t_prompt *prompt)
{
	int		count;
	int		i;
	t_parse	data;

	count = 0;
	i = -1;
	reset_bool(&data, 1);
	while (prompt->clean[++i])
	{
		check_quote(&data, prompt->clean[i]);
		if (prompt->clean[i] == '|'
			&& data.single_quote > 0 && data.double_quote > 0)
			count += 1;
	}
	prompt->nbr_request = count;
	prompt->requests = (t_request *) malloc ((count + 1) * sizeof(t_request));
	if (!prompt->requests)
		return (print_error(MEM, NULL, NULL));
	return (0);
}

int	separate_pipe(char *out, t_prompt *prompt)
{
	int	i;

	prompt->clean = out;
	if (count_pipe (prompt))
		return (1);
	if (set_request(prompt))
		return (1);
	i = 0;
	while (i <= prompt->nbr_request)
	{
		printf("[DEBUG 85] request[%d]-> len: %d, str: [%s]\n", i, prompt->requests[i].str_len ,prompt->requests[i].str);
		free (prompt->requests[i].str);
		i += 1;
	}
	free (prompt->requests);
	return (0);
}
