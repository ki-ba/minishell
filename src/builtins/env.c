#include "minishell.h"
#include "error.h"

int	ft_env(t_env_lst *env)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			if (printf("%s=\"%s\"\n", tmp->name, tmp->value) == -1)
				return (ERR_PRINT);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
