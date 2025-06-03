#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

/**
* @brief creates a random string starting with tmp_ and creates
* a file with resulting string as filename.
*/

static int	open_random_file(void)
{
	char	*random_str;
	char	*filename;
	int		hd_fd;

	random_str = create_random_str(HERE_DOC_LEN);
	filename = ft_concat(2, "tmp_", random_str);
	if (!filename)
		return (-1);
	while (!access(filename, F_OK))
	{
		ft_multifree(2, 0, random_str, filename);
		random_str = create_random_str(HERE_DOC_LEN);
		filename = ft_concat(2, "tmp_", random_str);
	}
	hd_fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (hd_fd > -1)
		unlink(filename);
	ft_multifree(2, 0, random_str, filename);
	return (hd_fd);
}

int	here_doc(char *delimiter)
{
	char	*line;
	int		hd_fd;

	hd_fd = open_random_file();
	if (hd_fd < 0)
		return (-1);
	line = NULL;
	write(1, "\nhere_doc_ish>", ft_strlen("\nhere_doc_ish> "));
	line = get_next_line(STDIN_FILENO);
	while (line && strncmp(line, delimiter, ft_strlen(delimiter)))
	{
		write(1, "\nhere_doc_ish> ", ft_strlen("\nhere_doc_ish> "));
		write(hd_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	return (hd_fd);
}
