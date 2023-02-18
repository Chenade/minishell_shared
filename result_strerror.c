
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(void)
{
	int		errnum = -1;
	char	*message;

	printf("[Error number & Error message List]\n\n");
	while (++errnum <= 255)
	{
		message = strerror(errnum);
		printf("(%d) %s\n", errnum, message);
	}
	return (0);
}

