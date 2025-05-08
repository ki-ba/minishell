#include "minishell.h"

void	ft_add_history(int hist_fd, char entry[], char last_cmd[])
{
	if (last_cmd)
	{
		ft_printf("comparing .%s. with .%s.\n",entry, last_cmd);
		if (!ft_strncmp(entry, last_cmd, ft_strlen(entry) + 1))
			return ;
	}
	write(hist_fd, entry, ft_strlen(entry));
	write(hist_fd, "\n", 1);
	add_history(entry);
}

int	retrieve_history(char *last_cmd[])
{
	int hist_fd;
	char	*hist_entry;
	hist_fd = open(HIST_FILE, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (hist_fd < 0)
		return (-1);
	hist_entry = get_next_line(hist_fd);
	while(hist_entry)
	{
		free(*last_cmd);
		*last_cmd = ft_strdup(hist_entry);
		(*last_cmd)[ft_strlen(*last_cmd) - 1] = '\0';
		add_history(hist_entry);
		free(hist_entry);
		hist_entry = get_next_line(hist_fd);
	}
	return (hist_fd);
}
