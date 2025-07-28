#include "libft.h"
#include "minishell.h"
#include <readline/history.h>

void	ft_add_history(char entry[])
{
	static char	last_cmd[255];

	if (entry)
	{
		if (!last_cmd[0] || ft_strncmp(entry, last_cmd, ft_strlen(entry) + 1))
		{
			add_history(entry);
			if (ft_strlcpy(last_cmd, entry, 255) > 255)
				ft_putstr_fd("warning : history entry truncated", 2);
		}
	}
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
