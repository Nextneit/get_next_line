/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:18:41 by ncruz-ga          #+#    #+#             */
/*   Updated: 2023/06/15 10:53:30 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	if (!str_res)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i] != '\0')
		str_res[j++] = str[i++];
	str_res[j] = '\0';
	return (free(str), str_res);
}

static char	*actual(char *str)
{
	char	*str_res;
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	str_res = ft_calloc((i + 1 + (str[i] == '\n')), sizeof(char));
	if (!str_res)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		str_res[i] = str[i];
		i++;
	}
	if (str[i] != '\0' && str[i] == '\n')
		str_res[i++] = '\n';
	str_res[i] = '\0';
	return (str_res);
}

static char	*join(char *str, char *buffer)
{
	char	*r;

	r = ft_strjoin(str, buffer);
	if (!r)
		return (NULL);
	return (r);
}

static char	*lot(int fd, char *str)
{
	char	*temp;
	int		read_char;

	temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!temp)
		return (free(str), NULL);
	read_char = 1;
	while (read_char > 0 && !ft_strchr(temp, '\n'))
	{
		read_char = read(fd, temp, BUFFER_SIZE);
		if (read_char < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[read_char] = '\0';
		str = join(str, temp);
		if (!str)
			return (free(str), free(temp), NULL);
	}
	return (free(temp), str);
}

char	*get_next_line(int fd)
{
	static char	*str[2048];
	char		*actual_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (str[fd] != NULL)
		{
			free(str[fd]);
			str[fd] = NULL;
		}
		return (NULL);
	}
	str[fd] = lot(fd, str[fd]);
	if (!str[fd])
		return (free(str[fd]), str[fd] = NULL, NULL);
	actual_line = actual(str[fd]);
	if (!actual_line)
		return (free(str[fd]), str[fd] = NULL, NULL);
	str[fd] = clean(str[fd]);
	if (!str[fd])
		return (free(str[fd]), str[fd] = NULL, actual_line);
	return (actual_line);
}
