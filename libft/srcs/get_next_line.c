/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 17:52:22 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 17:18:03 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_copy(char *dest, char *src)
{
	char *p;

	p = dest;
	if (dest && src)
	{
		while (*src)
			*dest++ = *src++;
		*dest = '\0';
	}
	return (p);
}

int					check_result(int read_bytes, char **storage, char **n)
{
	if (read_bytes || ft_strlen(*storage) || *n)
		return (1);
	else
	{
		if (*storage)
		{
			ft_free(*storage);
			*storage = NULL;
		}
		return (0);
	}
}

void				ft_newstr(char *n, char **line, char **storage)
{
	*n = '\0';
	ft_free(line);
	*line = ft_strdup(*storage);
}

char				*check_storage(char *store, char **line)
{
	char			*str;

	str = NULL;
	if (store && ft_strlen(store))
	{
		if ((str = ft_strchr(store, '\n')))
		{
			ft_newstr(str, line, &store);
			ft_copy(store, ++str);
		}
		else
		{
			ft_free(line);
			*line = ft_strdup(store);
			while (*store)
				*store++ = '\0';
		}
	}
	else
	{
		ft_free(line);
		*line = ft_strdup("\0");
	}
	return (str);
}

int					get_next_line(int fd, char **line)
{
	char			line_util[BUFFER_SIZE + 1];
	char			*n;
	static char		*storage;
	int				read_bytes;
	char			*temp;

	*line = NULL;
	n = check_storage(storage, line);
	while (!n && (read_bytes = read(fd, line_util, BUFFER_SIZE)))
	{
		if (read_bytes < 0 || fd < 0 || BUFFER_SIZE < 1 || !line)
			return (-1);
		line_util[read_bytes] = '\0';
		if ((n = ft_strchr(line_util, '\n')))
		{
			*n = '\0';
			ft_free(storage);
			if (!(storage = ft_strdup(++n)))
				return (-1);
		}
		temp = *line;
		*line = ft_strjoin(*line, line_util);
		ft_free(temp);
	}
	return (check_result(read_bytes, &storage, &n));
}
