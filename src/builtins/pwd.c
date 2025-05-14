#include "builtins.h"
#include <limits.h>

int	ft_pwd(char	*cmd)
{
	char	*path;

	path = NULL;
	if (ft_strncmp(cmd, "pwd\0", 4) != 0)
	{
		perror("minishell: pwd");
		return (1);
	}
	getcwd(path, PATH_MAX);
	if (!path)
	{
		perror("minishell: pwd");
		return (1);
	}
	return (0);
}
