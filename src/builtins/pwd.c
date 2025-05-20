#include "minishell.h"
#include "builtins.h"
#include "error.h"
#include <limits.h>

/**
 * @brief print the current directory
 * @param cmd is the command, with its options and arguments
 * @return 0 is the directory could be printed, non-zero otherwise
 */
int	ft_pwd(char **cmd)
{
	char	*path;

	path = ft_calloc(PATH_MAX, sizeof(char));
	if (cmd[1])
	{
		ft_putendl_fd("minishell: pwd: too many arguments", 2);
		return (1);
	}
	getcwd(path, PATH_MAX);
	if (!path)
	{
		ft_putendl_fd("minishell: pwd: couldn't get the path", 2);
		return (ERR_ALLOC);
	}
	printf("%s\n", path);
	free(path);
	return (SUCCESS);
}
