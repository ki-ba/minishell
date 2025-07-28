#include "minishell.h"

int	handle_shlvl(t_env_lst *new)
{
	int	prev_shlvl;

	prev_shlvl = ft_atoi(getenv("SHLVL"));
	new->value = ft_itoa(prev_shlvl + 1);
	if (prev_shlvl < 0 || prev_shlvl >= INT_MAX)
	{
		return (ft_putstr_fd("ERROR : SHLVL too high\n", 2));
		free(new->value);
	}
	else
		return (new->value == NULL);
}
