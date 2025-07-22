#include "minishell.h"

void	ft_add_history(int hist_fd, char entry[], char *last_cmd)
{
	if (last_cmd)
	{
		if (entry && entry[0] && !ft_strncmp(entry, last_cmd, ft_strlen(entry) + 1))
		{
			free(last_cmd);
			last_cmd = NULL;
			return ;
		}
		free(last_cmd);
	}
	write(hist_fd, entry, ft_strlen(entry));
	write(hist_fd, "\n", 1);
	add_history(entry);
}

int	retrieve_history(t_env_lst *env, char *last_cmd[])
{
	int		hist_fd;
	char	*hist_entry;
	char	*hist_fd_str;

	hist_fd = open(HIST_FILE, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (hist_fd < 0)
		return (-1);
	hist_entry = get_next_line(hist_fd);
	while (hist_entry)
	{
		hist_entry[ft_strlen(hist_entry) - 1] = '\0';
		free(*last_cmd);
		*last_cmd = ft_strdup(hist_entry);
		add_history(hist_entry);
		free(hist_entry);
		hist_entry = get_next_line(hist_fd);
	}
	hist_fd_str = ft_itoa(hist_fd);
	add_to_env(env, HIST_FILE, hist_fd_str, 1);
	free(hist_fd_str);
	return (hist_fd);
}
