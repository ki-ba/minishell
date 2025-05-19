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

int	str_swap(char *s1, char *s2)
{
	char	*cpy;

	cpy = ft_calloc(1, sizeof(char));
	cpy = ft_strdup(s2);
	if (!cpy)
		return (ERR_ALLOC);
	s2 = ft_strdup(s1);
	if (!s2)
	{
		free(cpy);
		return (ERR_ALLOC);
	}
	s1 = ft_strdup(cpy);
	if (!s1)
	{
		free(cpy);
		return (ERR_ALLOC);
	}
	free(cpy);
	return (SUCCESS);
}
