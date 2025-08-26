/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_input_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:35 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/04 16:08:38 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include "error.h"
#include "signals.h"
#include "minishell.h"
#include <errno.h>
#include <readline/readline.h>

/**
* @brief creates a random string starting with tmp_ and creates
* a file with resulting string as filename.
*/

static int	open_random_file(char **filename)
{
	char	*random_str;
	int		hd_fd;

	random_str = create_random_str(HERE_DOC_LEN);
	*filename = ft_concat(2, "tmp_", random_str);
	if (!filename)
		return (-1);
	while (!access(*filename, F_OK))
	{
		ft_multifree(2, 0, random_str, filename);
		random_str = create_random_str(HERE_DOC_LEN);
		*filename = ft_concat(2, "tmp_", random_str);
		if (!filename)
		{
			free(random_str);
			return (-1 * ERR_ALLOC);
		}
	}
	hd_fd = open(*filename, O_CREAT | O_WRONLY, 0644);
	free(random_str);
	return (hd_fd);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	rl_help(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

static void	fill_input(int fd, char del[], char *prompt)
{
	size_t	len;
	char	*line;

	line = NULL;
	rl_event_hook = rl_help;
	errno = 0;
	line = readline(prompt);
	len = ft_strlen(line);
	while (g_signal != 2
		&& line && ft_strncmp(line, del, ft_max(len, ft_strlen(del))))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		errno = 0;
		line = readline(prompt);
		if (errno)
			break ;
		len = ft_strlen(line);
	}
	rl_done = 0;
	rl_event_hook = NULL;
	if (!line && g_signal != 2)
		ft_putendl_fd("minishell: warning: ended with end of file", 2);
	free(line);
}

int	read_input(char *del)
{
	int		fd;
	char	*filename;

	update_signals(0);
	fd = open_random_file(&filename);
	if (fd < 0)
		return (fd);
	if (g_signal != 2)
		fill_input(fd, del, "input> ");
	if (fd > 0)
		close (fd);
	if (g_signal != 2)
		fd = open(filename, O_RDONLY);
	else
		fd = open(filename, O_RDWR | O_TRUNC);
	unlink(filename);
	free(filename);
	return (fd);
}
