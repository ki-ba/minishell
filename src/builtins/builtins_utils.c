#include "minishell.h"

t_env_lst	*search_env_var(t_env_lst *env, char *var)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, var, ft_strlen(tmp->name)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
