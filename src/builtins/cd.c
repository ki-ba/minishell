#include "minishell.h"
#include "builtins.h"
#include "error.h"
#include <limits.h>

static int	no_arg_cd(char **cmd, t_env_lst *env);
static int	update_env(char *new_path, t_env_lst *env);
static int	check_dir_access(char *new_path);

/** @brief if relative => check access from end to start */
/** @param cmd[0] is the cmd (here cd) */
/** @param cmd[1] is the new path */
/** @param cmd[2] should be NULL */
/** @return 0 on success or a non-zero int on failure */
int	ft_cd(char **cmd, t_env_lst *env)
{
	size_t	i;
	int		err;

	if (cmd[2] != NULL)
	{
		perror("minishell: cd: to many arguments\n");
		return (ERR_ARGS);
	}
	if (cmd[1] == NULL)
		return (no_arg_cd(cmd, env));
	if (cmd[1][0] == '\0')
		return (SUCCESS);
	i = ft_strlen(cmd[1]) - 1;
	if (i > 0 && cmd[1][i] == '/')
		cmd[1][i] = '\0';
	err = check_dir_access(cmd[1]);
	err = chdir(cmd[1]);
	if (err != 0)
	{
		perror("minishell: cd");
		return (err);
	}
	err = update_env(getcwd(cmd[1], PATH_MAX), env);
	return (err);
}

static int	check_dir_access(char *new_path)
{
	char	*full_path;
	size_t	i;
	size_t	j;
	int		err;

	i = 0;
	full_path = ft_calloc(1, sizeof(char));
	while (new_path[i] != '\0')
	{
		j = i + 1;
		while (new_path[j - 1] != '/' && new_path[j] != '\0')
			j++;
		full_path = ft_concat(2, full_path, ft_substr(new_path, i, j - i));
		err = access(full_path, R_OK | X_OK);
		if (err != 0)
		{
			perror("minishell: cd");
			break ;
		}
		i = j;
	}
	free (full_path);
	return (err);
}

static int	update_env(char *new_path, t_env_lst *env)
{
	t_env_lst	*head;
	t_env_lst	*tmp;

	head = env;
	tmp = search_env_var(env, "PWD");
	env = search_env_var(env, "OLDPWD");
	env->value = ft_strdup(tmp->value);
	if (!env->value)
	{
		perror("minishell: cd");
		return (ERR_ALLOC);
	}
	tmp->value = ft_strdup(new_path);
	if (!tmp->value)
	{
		perror("minishell: cd");
		return (ERR_ALLOC);
	}
	env = head;
	return (SUCCESS);
}

static int	no_arg_cd(char **cmd, t_env_lst *env)
{
	t_env_lst	*home;

	home = search_env_var(env, "HOME");
	if (!home || !(home->value))
	{
		cmd[1] = ft_strdup("/");
		if (!cmd[1])
			return (ERR_ALLOC);
	}
	else
	{
		cmd[1] = ft_strdup(home->value);
		if (!cmd[1])
			return (ERR_ALLOC);
	}
	ft_cd(cmd, env);
	return (0);
}
