/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:55:21 by ncruz-ga          #+#    #+#             */
/*   Updated: 2023/06/06 16:25:55 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean(char *str)
{
	int		i;
	int		j;
	char	*str_res;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	str_res = ft_calloc((ft_strlen(str) - i + 1), sizeof (char));
	i++;
	j = 0;
	while (str[i] != '\0')
		str_res[j++] = str[i++];
	free(str);
	if (str_res[0] == '\0')
	{
		free(str_res);
		return (NULL);
	}
	return (str_res);
}

static char	*actual(char *str)
{
	char	*str_res;
	int		i;

	i = 0;
	if (str[i] == 0)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	str_res = ft_calloc((i + 1 + (str[i] == '\n')), sizeof(char));
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		str_res[i] = str[i];
		i++;
	}
	if (str[i] != '\0' && str[i] == '\n')
		str_res[i++] = '\n';
	return (str_res);
}

static char	*join(char *str, char *buffer)
{
	char	*r;

	r = ft_strjoin(str, buffer);
	if (!r)
		return (NULL);
	return (free(str), r);
}

static char	*lot(int fd, char *str)
{
	char	*temp;
	int		read_char;

	if (!str)
		str = ft_calloc(1, sizeof(char));
	temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	read_char = 1;
	while (read_char > 0)
	{
		read_char = read(fd, temp, BUFFER_SIZE);
		if (read_char < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[read_char] = '\0';
		str = join(str, temp);
		if (ft_strchr (temp, '\n'))
			break ;
	}
	free(temp);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*actual_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (str != NULL)
		{
			free(str);
			str = NULL;
		}
		return (NULL);
	}
	str = lot(fd, str);
	actual_line = actual(str);
	str = clean(str);
	return (actual_line);
}

#include <fcntl.h>
#include <stdio.h>
int main ()
{
	int fichero;
	char *line;

	fichero = open("test.txt", O_RDONLY);
	line = get_next_line(fichero);
	while (line != NULL)
	{
		printf("%s\n", line);
		line = get_next_line(fichero);
	}
	close(fichero);
}