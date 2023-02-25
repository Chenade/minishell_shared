#include "minishell.h"

void	turn_sep(char *out)
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
			if (out[i] == '|' || out[i] == ' ' || out[i] == '<' || out[i] == '>')
		        out[i] = -(out[i]);
		}
		if (ft_isalpha(out[i]) || ft_isdigit(out[i]))
			reset_bool(&data, 0);
	}
}
