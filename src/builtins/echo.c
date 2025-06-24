#include "data_structures.h"
#include "libft.h"
#include "minishell.h"

int	ft_strcmp(char str1[], char str2[])
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		++i;
	}
	return (str1[i] - str2[i]);
}

// TODO: check why not working if echo -n $?
size_t	has_option(char **cmd, char opt)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (!cmd[i] || cmd[i][0] != '-')
		return (1);
	while (cmd[i])
	{
		j = 1;
		while (cmd[i][j])
		{
			if (cmd[i][j] != opt)
				return (i);
			++j;
		}
		++i;
	}
	return (i);
}

int	ft_echo(char **cmd, t_env_lst *env)
{
	size_t	i;
	size_t	opt;

	(void) env;
	opt = has_option(cmd, 'n');
	i = opt;
	while (i && cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i] && cmd[i + 1])
			ft_printf(" ");
		++i;
	}
	if (opt == 1)
		ft_printf("\n");
	// destroy_env_lst(env);
	return (SUCCESS);
}
