/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgastal- <fgastal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:47:01 by fgastal-          #+#    #+#             */
/*   Updated: 2022/05/08 23:29:37 by fgastal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

static char	*get_comp(int fd, char *buffer,
char *accumulator, char *current_line)
{
	int		i;

	i = 1;
	while (!ft_strchr(accumulator, '\n') && i)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (NULL);
		if (!accumulator)
		{
			accumulator = (char *)malloc(1);
			accumulator[0] = '\0';
		}
		buffer[i] = '\0';
		current_line = accumulator;
		accumulator = ft_strjoin(current_line, buffer);
		free(current_line);
	}
	return (accumulator);
}

char	*get_next_line(int fd)
{
	static char	*accumulator[1024];
	char		*buffer;
	char		*current_line;

	if (read(fd, 0, 0) == -1)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	current_line = NULL;
	accumulator[fd] = get_nl(fd, buffer, accumulator[fd], current_line);
	free(buffer);
	current_line = ft_strnldup(accumulator[fd]);
	accumulator[fd] = verif(accumulator[fd]);
	return (current_line);
}
