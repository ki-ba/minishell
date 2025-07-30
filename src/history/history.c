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
