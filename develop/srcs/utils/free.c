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

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	free_token(t_token **token)
{
	t_token	*ptr;

	ptr = (*token);
	if (!ptr)
		return ;
	while (ptr->next)
	{
		ptr = ptr->next;
		free(ptr->prev->str);
		free(ptr->prev);
	}
	if (ptr)
	{
		free(ptr->str);
		free(ptr);
	}
	*token = NULL;
}

void free_all(t_prompt *p)
{
	t_token	*tmp;

	free_matrix(&p->envp);
	ft_close(p->input_fd);
	ft_close(p->output_fd);
}
