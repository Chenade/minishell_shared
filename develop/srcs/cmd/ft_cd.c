
#include "minishell.h"

int	ft_cd(int i, t_prompt *prompt)
{
	t_token	*token;

	token = move_to(prompt->token, i);
	while (token)
	{
		if (token->type != 2)
			break ;
		ft_putstr_fd (token->str, 1);
		ft_putstr_fd (" ", 1);
		token = token->next;
	}
	ft_putendl_fd("", 1);
	return (0);
}