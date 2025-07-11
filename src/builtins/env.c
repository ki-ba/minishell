#include "minishell.h"
#include "builtins.h"
#include "error.h"

int	ft_env(char **cmd, t_env_lst *env)
{
	t_env_lst	*tmp;

	if (cmd[1])
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (ERR_ARGS);
	}
	tmp = env;
	while (tmp)
	{
		if (tmp->value && check_name_validity(tmp->name) == SUCCESS)
		{
			if (printf("%s=\"%s\"\n", tmp->name, tmp->value) == -1)
				return (ERR_PRINT);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_name_validity(char *name)
{
	int	i;

	if (!isalpha(name[0]) && name[0] != '_')
		return (ERR_ARGS);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!isalnum(name[i]) && name[i] != '_')
			return (ERR_ARGS);
		i++;
	}
	return (SUCCESS);
}
