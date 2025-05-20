#include "minishell.h"
#include "error.h"
#include "builtins.h"

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

/**
 * @brief check which command is pass and call the corresponding function
 * @param cmd is the command, its options and its arguments
 * @param env is the environment
 * @return 0 if command was successful, non-zero if failure
 */
int	builtins_call(char **cmd, t_env_lst *env)
{
	int	err;

	if (!cmd[0])
		return (SUCCESS);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		err = ft_cd(cmd, env);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		err = ft_pwd(cmd);
	else
		err = printf("not a builtin\n");
	return (err);
}
