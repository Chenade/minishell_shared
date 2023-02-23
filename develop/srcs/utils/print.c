#include "minishell.h"

void	print_token(t_token *token)
{
	int	i;
	t_token *tmp;

	i = 1;
	tmp = token;
	// printf("======print_token======\n");
	while (tmp->str)
	{
		printf("		%d ) STR : %15s  TYPE : %d  \n", i++, tmp->str, tmp->type);
		if (!tmp->next)
			break;
		tmp = tmp->next;
	}
	// printf("======print_token======\n");
}

int	print_env(char **envp)
{
	int i;

	i = 0;
	while(envp && envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
