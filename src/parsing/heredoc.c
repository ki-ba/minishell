#include "minishell.h"

int	here_doc(char *delimiter)
{
	char	*filename;
	char	*line;
	int		hd_fd;

	filename = create_random_str(HERE_DOC_LEN);
	if (!filename)
		exit(EXIT_FAILURE);
	hd_fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (hd_fd < 0)
		exit(EXIT_FAILURE);
	line = NULL;
	write(1, "here_doc_ish", ft_strlen("here_doc_ish"));
	line = get_next_line(STDIN_FILENO);
	while (line && strncmp(line, delimiter, ft_strlen(delimiter)))
	{
		write(1, "here_doc_ish> ", ft_strlen("here_doc_ish> "));
		write(hd_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	return (hd_fd);
}
