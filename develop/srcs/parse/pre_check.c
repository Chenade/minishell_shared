/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:07:13 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/26 00:32:01 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset_bool(t_parse *data, int init)
{
	data->infile = 0;
	data->outfile = 0;
	data->is_pipe = 1;
	if (init)
	{
		data->is_pipe = -1;
		data->single_quote = 1;
		data->double_quote = 1;
	}
	return (0);
}

int	check_pipe(t_parse *data, char *c, t_prompt *prompt)
{
	if (*c == '|')
	{
		prompt->nbr_request++;
		if (data->is_pipe < 0 || data->outfile || data->infile)
			return (1);
		data->is_pipe *= -1;
	}
	return (0);
}

int	check_redirect(t_parse *data, char *c)
{
	if (*c == '<')
	{
		if (data->outfile > 0)
			return (1);
		data->infile += 1;
		if (data->infile > 2)
			return (1);
	}
	if (*c == '>')
	{
		if (data->infile > 0)
			return (1);
		data->outfile += 1;
		if (data->outfile > 2)
			return (1);
	}
	if (*c == ' ')
	{
		if (data->infile > 0)
			data->infile += 1;
		if (data->outfile > 0)
			data->outfile += 1;
	}
	return (0);
}

int	check_quote(t_parse *data, char c)
{
	if (c == '\"' && data->single_quote > 0)
	{
		data->double_quote *= -1;
		reset_bool(data, 0);
	}
	if (c == '\'' && data->double_quote > 0)
	{
		data->single_quote *= -1;
		reset_bool(data, 0);
	}
	return (0);
}

int	pre_check(char *out, t_prompt *prompt)
{
	int		i;
	t_parse	data;

	i = -1;
	prompt->nbr_request = 1;
	reset_bool(&data, 1);
	while (out[++i])
	{
		check_quote(&data, out[i]);
		if (data.double_quote > 0 && data.single_quote > 0)
		{
			if (check_pipe(&data, &(out[i]), prompt))
				break ;
			if (check_redirect (&data, &(out[i])))
				break ;
		}
		if (ft_isalpha(out[i]) || ft_isdigit(out[i]))
			reset_bool(&data, 0);
	}
	return (print_syntax_error(data, out));
}
