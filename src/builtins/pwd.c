#include "data_structures.h"
#include "minishell.h"
#include "builtins.h"
#include "error.h"
#include <limits.h>

/**
 * @brief print the current directory
 * @param cmd is the command, with its options and arguments
 * @return 0 is the directory could be printed, non-zero otherwise
 */
int	ft_pwd(char **cmd, t_env_lst *env)
{
	char	*path;

	(void)env;
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
	ft_printf("%s\n", path);
	free(path);
	return (SUCCESS);
}
