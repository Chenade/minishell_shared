/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:44:37 by ykuo              #+#    #+#             */
/*   Updated: 2022/08/15 09:06:32 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cut_line(char *line)
{
	int	i;

	i = -1;
	while (line && line[++i])
	{
		if (line[i] == 10)
			return (i + 1);
	}
	return (0);
}

static size_t	gnl_strlen(const char *s)
{
	size_t	ans;

	ans = 0;
	if (!s)
		return (ans);
	while (s[ans])
		ans += 1;
	return (ans);
}

static char	*gnl_ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2[0])
		return (s1);
	if (cut_line(s2) > 0)
		ret = malloc(sizeof(char) * (gnl_strlen(s1) + cut_line(s2) + 1));
	else
		ret = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!ret)
		return (0);
	while (s1 && s1[i])
		ret[i++] = s1[j++];
	j = 0;
	while (s2[j] && s2[j] != '\n')
		ret[i++] = s2[j++];
	if (s2[j] == '\n')
		ret[i++] = s2[j];
	ret[i] = 0;
	free(s1);
	return (ret);
}

static void	clear_buffer(char *buffer)
{
	int	i;
	int	pos;

	i = 0;
	pos = cut_line(buffer);
	while (buffer[pos + i] && pos)
	{
		buffer[i] = buffer[pos + i];
		i += 1;
	}
	buffer[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			ret;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = gnl_ft_strjoin(line, buffer);
	ret = 1;
	while (ret > 0 && !cut_line(line))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
			return (free(line), NULL);
		buffer[ret] = '\0';
		line = gnl_ft_strjoin(line, buffer);
	}
	clear_buffer (buffer);
	return (line);
}
