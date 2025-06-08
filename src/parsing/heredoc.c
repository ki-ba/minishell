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

static void	fill_here_doc(int hd, char del[])
{
	size_t	len;
	size_t	dlen;
	char	*line;

	line = NULL;
	write(1, "\nhere_doc_ish>", ft_strlen("\nhere_doc_ish> "));
	line = get_next_line(STDIN_FILENO);
	len = ft_strlen(line);
	dlen = ft_strlen(del);
	while (line && ft_strncmp(line, del, ft_max(len - 1, dlen)))
	{
		write(1, "\nhere_doc_ish> ", ft_strlen("\nhere_doc_ish> "));
		write(hd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
		len = ft_strlen(line);
	}
	free(line);
}

int	here_doc(char *del)
{
	int		hd_fd;
	char	*filename;

	hd_fd = open_random_file(&filename);
	if (hd_fd < 0)
		return (hd_fd);
	fill_here_doc(hd_fd, del);
	close (hd_fd);
	hd_fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	return (hd_fd);
}
