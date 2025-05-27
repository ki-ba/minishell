#include "minishell.h"
#include "error.h"

int	ft_export(char **cmd, t_env_lst *env)
{
	if (!cmd[1])
	{
		ft_putendl_fd("minishell: export: not enough arguments", 2);
		return (ERR_ARGS);
	}
	int i;
	i = 2;
	while (cmd[i])
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(cmd[i], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (ERR_ARGS);
	}
	
	return (SUCCESS);
}
