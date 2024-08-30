/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalle-d <jvalle-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:40:06 by jvalle-d          #+#    #+#             */
/*   Updated: 2024/06/12 10:43:27 by jvalle-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_joinfree(char *buffer, char *aux)
{
	char	*temp;

	temp = ft_strjoin(buffer, aux);
	free(buffer);
	return (temp);
}

char	*ft_readbuffer(char *buffer, int fd)
{
	int		i;
	char	*aux;

	if (!buffer)
	{
		buffer = ft_calloc(1, 1);
		if (!buffer)
			return (NULL);
	}
	aux = ft_calloc(BUFFER_SIZE + 1, 1);
	i = 1;
	while ((!ft_strchr(aux, '\n')) && i > 0)
	{
		i = read(fd, aux, BUFFER_SIZE);
		if (i == -1)
			return (free(aux), NULL);
		aux[i] = '\0';
		buffer = ft_joinfree(buffer, aux);
		if (!buffer)
			return (NULL);
	}
	free(aux);
	return (buffer);
}

char	*ft_readline(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 1 + (buffer[i] == '\n'), 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_updatebuffer(char *buffer)
{
	int		i;
	int		j;
	char	*update;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (ft_free(buffer));
	update = ft_calloc((ft_strlen(buffer) - i + 1), 1);
	if (!update)
		return (ft_free(buffer));
	i++;
	j = 0;
	while (buffer[i])
		update[j++] = buffer[i++];
	free(buffer);
	return (update);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_SETSIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = ft_readbuffer(buffer[fd], fd);
	if (!buffer[fd])
		return (ft_free(buffer[fd]));
	line = ft_readline(buffer[fd]);
	buffer[fd] = ft_updatebuffer(buffer[fd]);
	return (line);
}

/*#include <stdio.h>
int main ()
{
	int fd;
	int fd2;
	int fd3;
	char *print;
	fd = open("archivo.txt", O_RDONLY);
	fd2 = open("archivo2.txt", O_RDONLY);
	fd3 = open("archivo3.txt", O_RDONLY);
	
	
	while ((print = get_next_line(fd)) != NULL)
	{
		printf("Linea: %s\n",print);
		free (print);	
	}
	while ((print = get_next_line(fd2)) != NULL)
	{
		printf("Linea: %s\n",print);
		free (print);	
	}
	while ((print = get_next_line(fd3)) != NULL)
	{
		printf("Linea: %s\n",print);
		free (print);	
	}
	close (fd);
	close (fd2);
	close (fd3);
	return (0);
}
*/