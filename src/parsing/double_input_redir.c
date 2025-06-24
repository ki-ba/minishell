#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

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

static void	fill_input(int fd, char del[], char *prompt)
{
	size_t	len;
	size_t	dlen;
	char	*line;

	line = NULL;
	write(1, prompt, ft_strlen(prompt));
	line = get_next_line(STDIN_FILENO);
	len = ft_strlen(line);
	dlen = ft_strlen(del);
	while (line && ft_strncmp(line, del, ft_max(len - 1, dlen)))
	{
		write(1, prompt, ft_strlen(prompt));
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
		len = ft_strlen(line);
	}
	if (!line && g_return != 130)
	{
		ft_printf_fd(2,
			"\nminishell: warning: ended with end of file instead of '%s'\n",
			 del);
	}
	free(line);
}

int	read_input(char *del)
{
	int		fd;
	char	*filename;

	update_signals(1);
	fd = open_random_file(&filename);
	if (fd < 0)
		return (fd);
	if (g_return != 130)
		fill_input(fd, del, "input> ");
	close (fd);
	if (g_return != 130)
		fd = open(filename, O_RDONLY);
	else
		fd = open(filename, O_RDWR | O_TRUNC);
	unlink(filename);
	free(filename);
	return (fd);
}
