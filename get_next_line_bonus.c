#include "get_next_line_bonus.h"

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

static char	*get_nl(int fd, char *buffer, char *str, char *save)
{
	int		i;

	i = 1;
	while (!ft_strchr(str, '\n') && i)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (NULL);
		if (!str)
		{
			str = (char *)malloc(1);
			str[0] = '\0';
		}
		buffer[i] = '\0';
		save = str;
		str = ft_strjoin(save, buffer);
		free(save);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[1024]; // Considerando-se um limite máximo de 1024 para o conteúdo dessa variável
	char		*buffer;
	char		*save;

	if (read(fd, 0, 0) == -1)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	save = NULL;
	str[fd] = get_nl(fd, buffer, str[fd], save); // Aqui, é a única parte do bônus que realmente muda, pois adicionamos um conteúdo ao valor da string (seria o file descriptor)
	free(buffer); // A ideia disso é que seja adaptável ao valor a ser considerado para fd, assim como fizemos para o buffer
	save = ft_strnldup(str[fd]);
	str[fd] = ft_exstrchr(str[fd]);
	return (save);
}
