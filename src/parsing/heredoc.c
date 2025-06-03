#include "minishell.h"

int	here_doc(char *delimiter)
{
	char	*filename;
	char	*line;
	int		hd_fd;

	filename = ft_concat(2, "tmp_", create_random_str(HERE_DOC_LEN));
	if (!filename)
		return (-1);
	hd_fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (hd_fd < 0)
		return (-1);
	unlink(filename);
	line = NULL;
	write(1, "\nhere_doc_ish>", ft_strlen("\nhere_doc_ish> "));
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)))
	{
		write(1, "\nhere_doc_ish> ", ft_strlen("\nhere_doc_ish> "));
		write(hd_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	return (hd_fd);
}
