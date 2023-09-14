/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 08:42:49 by mlamkadm          #+#    #+#             */
/*   Updated: 2023/09/14 17:41:21 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_cleanup_line(char *appended_line, size_t len);
static char	*ft_append_line(int fd, char *read_buffer, char *static_buffer);

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	char		*read_buffer;
	char		*appended_line;
	size_t		len;

	if (BUFFER_SIZE > 0)
		read_buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	if (fd < 0  || read(fd, 0, 0) < 0)
	{
		free(static_buffer);
		free(read_buffer);
		static_buffer = NULL;
		read_buffer = NULL;
		return (NULL);
	}
	appended_line = ft_append_line(fd, read_buffer, static_buffer);
	if (!appended_line)
		free(appended_line);
	free(read_buffer);

	read_buffer = NULL;
	if (!appended_line)
	{
		free(appended_line);
	}
	len = ft_strlen(appended_line);
	static_buffer = ft_cleanup_line(appended_line, len);
	return (appended_line);
}

static char	*ft_cleanup_line(char *appended_line, size_t len)
{
	char	*remainder;
	ssize_t	i;

	i = 0;
	while (appended_line[i] != '\n' && appended_line[i] != '\0')
		i++;
	if (appended_line[i] == '\0') 
		return (NULL);
	remainder = ft_substr(appended_line, i + 1, len - i);
	if (*remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	appended_line[i + 1] = '\0';
	return (remainder);
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


int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	int	i = 0;
	int j = 1; 
	// void *p;
	while (i < j)
	{
		printf("%s",get_next_line(fd));
		i++;
	}
	return 0;	
}