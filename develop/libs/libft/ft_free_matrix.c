#include "libft.h"

void	ft_free_matrix(char **str)
{
	int		i;

    i = 0;
	if (str == NULL)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}
