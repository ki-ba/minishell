#include "libft.h"
#include "minishell.h"
#include "error.h"
#include "builtins.h"

t_env_lst	*search_env_var(t_env_lst *env, char *var)
{
	t_env_lst	*tmp;
	size_t		max_len;

	tmp = env;
	max_len = ft_strlen(var);
	while (tmp)
	{
		if (ft_strlen(tmp->name) > max_len)
			max_len = ft_strlen(tmp->name);
		if (ft_strncmp(tmp->name, var, max_len + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
