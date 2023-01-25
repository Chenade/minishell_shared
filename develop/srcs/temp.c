#include "minishell.h"

void	print_token(t_token *token)
{
	int	i;

	i = 1;
	while (token->str)
	{
		printf("%d ) STR : %15s  TYPE : %d  \n",i++, token->str, token->type);
		if (!token->next)
			break;
		token = token->next;
	}
}

void	print_env(char **envp)
{
	int i;

	i = -1;
	while(envp[++i])
		printf("%d : %s\n", i + 1, envp[i]);
}
