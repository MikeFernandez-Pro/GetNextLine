/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifernan <mifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:16:42 by mifernan          #+#    #+#             */
/*   Updated: 2019/12/03 13:30:00 by mifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_find_n(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_reader(int fd, char *rest, char buf[])
{
	int		ret;

	while (!(ft_strchr(rest, '\n')) && (ret = read(fd, buf, BUFFER_SIZE))
		&& *buf)
	{
		if (ret == -1)
			return (NULL);
		buf[ret] = '\0';
		if (!(rest = ft_strjoin(rest, buf)))
			return (NULL);
	}
	free(buf);
	return (rest);
}

int		ft_last_line(char *rest, char **line)
{
	*line = strndup(rest, ft_strlen(rest));
	if (*rest)
		free(rest);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*rest;
	char		*tmp;
	int			i;
	char		*buf;

	if (!(buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || (read(fd, buf, 0) < 0)
	|| (!rest && !(rest = malloc(sizeof(char) * 1))))
		return (-1);
	if (!rest)
		rest = NULL;
	i = 0;
	rest = ft_reader(fd, rest, buf);
	if (!ft_strchr(rest, '\n'))
		return (ft_last_line(rest, line));
	while (rest[i] != '\n' && rest[i])
		i++;
	*line = ft_strndup(rest, i);
	tmp = ft_strdup(ft_strchr(rest, '\n') + 1);
	free(rest);
	rest = ft_strndup(tmp, ft_strlen(tmp));
	free(tmp);
	return (1);
}
