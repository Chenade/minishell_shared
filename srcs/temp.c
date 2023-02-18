#include "minishell.h"

void	print_token(t_token *token)
{
	int	i;

	i = 1;
	printf("======print_token======\n");
	while (token->str)
	{
		printf("%d ) STR : %15s  TYPE : %d  \n", i++, token->str, token->type);
		if (!token->next)
			break;
		token = token->next;
	}
	printf("======print_token======\n");
}

int	print_env(char **envp)
{
	int i;

	i = -1;
	printf("======print_env======\n");
	while(envp[++i])
		printf("%d : %s\n", i + 1, envp[i]);
	printf("======print_env======\n");
	return (0);
}
