#include "libft.h"

void	dupnclose(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	ft_close(oldfd);
}