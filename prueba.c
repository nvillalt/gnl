/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:10:25 by nvillalt          #+#    #+#             */
/*   Updated: 2023/10/26 19:32:16 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line_bonus.h"

char	*ft_free_saved(int fd, char *saved[fd])
{
	char	*aux;
	int		len;

	len = 0;
	while (saved[fd][len] != '\0' && saved[fd][len] != '\n')
		len++;
	if (saved[fd][len] == '\n')
		len++;
	aux = ft_strdup(saved[fd] + len);
	free(saved[fd]);
	if (!aux)
		return (NULL);
	return (aux);
}

char	*ft_get_returned_line(int fd, char *saved[fd])
{
	char	*final;
	int		len;

	len = 0;
	if (!saved[fd] || saved[fd][len] == '\0')
		return (NULL);
	while (saved[fd][len] != '\0' && saved[fd][len] != '\n')
		len++;
	if (saved[fd][len] ==  '\n')
		len++;
	final = ft_calloc(sizeof(char), len + 1); 	
	if (!final)
		return (NULL);
	len = 0;
	while (saved[fd][len] != '\n' && saved[fd][len] != '\0')
	{
		final[len] = saved[fd][len];
		len++;
	}
	if (saved[fd][len] == '\n')
		final[len] = saved[fd][len];
	return (final);
}

char	*ft_read_fd(int fd, char *saved[fd])
{
	char	*buffer; 
	ssize_t	read_chars;

	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_chars = 1;
	while (read_chars > 0 && !ft_check_char(buffer, '\n'))
	{
		read_chars = read(fd, buffer, BUFFER_SIZE);
		if (read_chars == -1)
		{
			free(buffer);
			free(saved[fd]);
			saved[fd] = 0;
			return (NULL);
		}
		buffer[read_chars] = '\0';
		saved[fd] = ft_strjoin(saved[fd], buffer);
	}
	free(buffer);
	return (saved[fd]);
}

char	*get_next_line(int fd)
{
	static char	*saved[FD_MAX];
	char		*final;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(saved[fd]), NULL);
	saved[fd] = ft_read_fd(fd, &saved[fd]);
	if (!saved[fd])
		return (NULL);
	final = ft_get_returned_line(fd, &saved[fd]);
	if (!final)
	{
		if (saved[fd])
		{
			free(saved[fd]);
			saved[fd] = 0;
			return (NULL);
		}
	}
	saved[fd] = ft_free_saved(fd, &saved[fd]);
	return (final);
}