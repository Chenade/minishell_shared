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
	// free(*token);
	*token = NULL;
}

void	free_all(t_prompt *p)
{
	int	i;

	i = 0;
	while (i < p->nbr_request)
	{
		if (p->requests)
		{
			if (p->requests[i].token)
			{
				free_token(&(p->requests[i].token));
			}
			free(p->requests[i].str);
			ft_close(p->requests->input_fd);
			ft_close(p->requests->output_fd);
		}
		i++;
	}
	free(p->requests);
	free (p->clean);
}

// void	free_readline(char **out, t_prompt *prompt)
// {
// 	int	i;

// 	i = 0;
// 	free (*out);
// 	while (i <= prompt->nbr_request)
// 	{
// 		// printf("[DEBUG 85] request[%d]-> len: %d, str: [%s]\n", i, prompt->requests[i].str_len ,prompt->requests[i].str);
// 		free (prompt->requests[i].str);
// 		i += 1;
// 	}
// 	free (prompt->requests);
// }