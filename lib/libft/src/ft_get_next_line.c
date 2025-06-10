/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:41:21 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 17:41:31 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* appends (joins) the characters of `buffer` into `line` until the
 * fist newline.
 * Removes the copied chars from `buffer`.
 * @param buffer the string to copy from.
 * @param line the string to copy to.
 */
char	*join_to_line(char *line[], char buffer[])
{
	size_t	n;
	size_t	i;
	char	*longer_line;

	if (!*line)
	{
		*line = malloc(1 * sizeof(char));
		if (!*line)
			return (NULL);
		*line[0] = '\0';
	}
	n = 0;
	while (buffer[n] && buffer[n] != '\n')
		++n;
	longer_line = ft_strnjoin(*line, buffer, n);
	free(*line);
	*line = longer_line;
	ft_memmove(buffer, &buffer[n + 1], BUFFER_SIZE - n);
	i = BUFFER_SIZE - n;
	while (i <= BUFFER_SIZE)
	{
		buffer[i] = '\0';
		++i;
	}
	return (*line);
}

/*
 * @return a `char *` containing the next line of the file `fd`.
 * @return `NULL` if EOF reached, or if an error happened.
 * @param fd the file descriptor of the file to read from.
 */
char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	char		*line;
	ssize_t		n_read;

	line = NULL;
	while (!ft_strchr(line, '\n') && fd >= 0 && BUFFER_SIZE > 0)
	{
		if (buffer[fd][0] == '\0')
		{
			n_read = read(fd, buffer[fd], BUFFER_SIZE);
			if (n_read < 0)
				return (free(line), NULL);
			else if (n_read == 0)
				return (line);
			buffer[fd][n_read] = '\0';
			if (n_read < BUFFER_SIZE)
				return (join_to_line(&line, buffer[fd]));
		}
		join_to_line(&line, buffer[fd]);
	}
	return (line);
}
