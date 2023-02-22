# include "libft.h"

void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}