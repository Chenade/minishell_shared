#include "minishell.h"

int	print_syntax_error(t_parse data)
{
	if (data.single_quote < 0)
		return (print_error(SYNERR, "", "'"));
	if (data.double_quote < 0)
		return (print_error(SYNERR, "", "\""));
	if (data.is_pipe < 0 && data.infile == 0 && data.outfile == 0)
		return (print_error(SYNERR, "", "|"));
	if (data.infile > 0)
		return (print_error(SYNERR, "", "<"));
	if (data.outfile > 0)
		return (print_error(SYNERR, "", ">"));
	return (0);
}

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

int	check_redirect(t_parse *data, char c)
{
	if (c == '<')
	{
		if (data->outfile > 0)
			return (1);
		data->infile += 1;
		if (data->infile > 2)
			return (1);
	}
	if (c == '>')
	{
		if (data->infile > 0)
			return (1);
		data->outfile += 1;
		if (data->outfile > 2)
			return (1);
	}
	if (c == ' ')
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
	if (c == '"' && data->single_quote > 0)
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

int	pre_check(char *out)
{
	int		i;
	t_parse	data;

	i = -1;
	reset_bool(&data, 1);
	while (out[++i])
	{
		check_quote(&data, out[i]);
		if (data.double_quote > 0 && data.single_quote > 0)
		{
			if (out[i] == '|')
			{
				if (data.is_pipe < 0)
					break ;
				data.is_pipe *= -1;
			}
			if (check_redirect (&data, out[i]))
				break ;
		}
		if (ft_isalpha(out[i]))
			reset_bool(&data, 0);
	}
	return (print_syntax_error(data));
}
