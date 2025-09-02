/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_input_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:35 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/02 11:01:51 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"
#include <readline/readline.h>

/**
 * @brief creates a random filename that doesn't exist in current directory.
 */
static char	*create_filename(void)
{
	char	*random_str;
	char	*filename;

	random_str = create_random_str(HERE_DOC_LEN);
	if (!random_str)
		return (NULL);
	filename = ft_concat(2, "tmp_", random_str);
	free(random_str);
	random_str = NULL;
	if (!filename)
		return (NULL);
	while (!access(filename, F_OK))
	{
		ft_multifree(2, 0, random_str, filename);
		random_str = create_random_str(HERE_DOC_LEN);
		if (!random_str)
			return (NULL);
		filename = ft_concat(2, "tmp_", random_str);
		if (!(filename))
		{
			free(random_str);
			return (NULL);
		}
	}
	return (filename);
}

/**
 * @brief creates a file with a random name and opens it in reading
 * @brief and writing, saving the resulting fds in an array.
*/
static int	open_random_file(int fd[2])
{
	char	*filename;

	filename = create_filename();
	if (!filename)
		return (-1);
	fd[1] = open(filename, O_CREAT | O_WRONLY, 0644);
	if (fd[1] > 0)
		fd[0] = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	return (fd[0] < 0 || fd[1] < 0);
}

static int	rl_help(void)
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
	line = readline(prompt);
	len = ft_strlen(line);
	while (g_signal != 2
		&& line && ft_strncmp(line, del, ft_max(len, ft_strlen(del))))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(prompt);
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
	int		fd[2];
	int		err;

	update_signals(0);
	err = open_random_file(fd);
	if (err)
		return (err);
	if (g_signal != 2)
		fill_input(fd[1], del, "input> ");
	if (fd[1] > 0)
		close (fd[1]);
	return (fd[0]);
}
