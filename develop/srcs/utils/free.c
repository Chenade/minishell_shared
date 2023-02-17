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

void free_token(t_token **token)
{
	t_token	*tmp;

	tmp = (*token);
	if (!tmp)
		return ;
	while (tmp->next)
	{
		tmp = tmp->next;
		free(tmp->prev->str);
		free(tmp->prev);
	}
	if (tmp)
	{
		free(tmp->str);
		free(tmp);
	}
	*token = NULL;
}
