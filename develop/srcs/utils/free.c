#include "minishell.h"

void	free_pp(char **pp)
{
	int		i;

    i = 0;
	if (pp == NULL)
		return ;
	while (pp[i])
		free(pp[i++]);
	free(pp);
}

void	free_matrix(char ***m)
{
	int	i;

	i = 0;
	while (m && m[0] && m[0][i])
	{
		free(m[0][i]);
		i++;
	}
	if (m)
	{
		free(m[0]);
		*m = NULL;
	}
}

void free_all(t_prompt *p)
{
	t_token	*tmp;

	// free_matrix(&p->envp);
	while (p->token)
	{
		tmp = (p->token)->next;
		free(p->token->str);
		free(p->token);
		(p->token) = tmp;
	}
}
