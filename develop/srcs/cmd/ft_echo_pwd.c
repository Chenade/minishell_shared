
#include "minishell.h"

int	ft_pwd(t_prompt *prompt)
{
	ft_putstr_fd (get_env("PWD", prompt->envp, 1), 1);
	ft_putendl_fd("", 1);
	return (0);
}

int	ft_echo(int i, t_prompt *prompt)
{
	t_token	*token;

	token = move_to(prompt->token, i);
	while (token)
	{
		if (token->type == 2)
		{
			ft_putstr_fd (token->str, 1);
			if (token->next && token->next->type == 2)
				ft_putstr_fd (" ", 1);
		}
		else if (token->type == 4)
			ft_putstr_fd (get_env(token->str, prompt->envp, 1), 1);
		else
			break ;
		token = token->next;
	}
	ft_putendl_fd("", 1);
	return (0);
}