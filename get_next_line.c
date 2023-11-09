/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 08:42:49 by mlamkadm          #+#    #+#             */
/*   Updated: 2023/09/15 00:39:53 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_cleanup_line(char *appended_line);
static char	*ft_append_line(int fd, char *read_buffer, char *static_buffer);

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	char		*read_buffer;
	char		*appended_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(static_buffer);
		static_buffer = NULL;
		return (NULL);
	}
	read_buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	appended_line = ft_append_line(fd, read_buffer, static_buffer);
	free(read_buffer);
	if (!appended_line)
		return (NULL);
	static_buffer = ft_cleanup_line(appended_line);
	return (appended_line);
}

static char	*ft_cleanup_line(char *appended_line)
{
	char	*line;
	ssize_t	i;

	i = 0;
	while (appended_line[i] != '\n' && appended_line[i] != '\0')
		i++;
	if (appended_line[i] == '\0') 
		return (NULL);
	else
		line = ft_substr(appended_line, i + 1, ft_strlen(appended_line) - i);
	if (*line == '\0')
	{
		free(line);
		line = NULL;
	}
	appended_line[i + 1] = '\0';
	return (line);
}

static char	*ft_append_line(int fd, char *read_buffer, char *static_buffer)
{
	ssize_t	bread;
	char	*temp;

	bread = 1;
	while (bread > 0)
	{
		bread = read(fd, read_buffer, BUFFER_SIZE);
		if (bread == -1)
		{
			free(static_buffer);
			return (NULL);
		}
		if (bread == 0)
			break ;
		read_buffer[bread] = '\0';
		if (!static_buffer)
			static_buffer = ft_strdup("");
		temp = static_buffer;
		static_buffer = ft_strjoin(temp, read_buffer);
		free(temp);
		temp = NULL;
		if (ft_find_nl(read_buffer, '\n') == 1)
			break ;
	}
	return (static_buffer);
}
