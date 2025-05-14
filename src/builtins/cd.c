#include "minishell.h"
#include "builtins.h"
#include <limits.h>

static int	no_arg_cd(t_env_lst *env);
static int	update_env(char *new_path, t_env_lst *env);
static int	check_dir_access(char *new_path);

/** @brief if relative => check access from end to start */
/** @param  */
/** @param */
/** @return  */
int	ft_cd(char *new_path, t_env_lst *env)
{
	size_t	i;
	int		err;

	if (new_path[0] == '\0')
		return (no_arg_cd(env));
	i = ft_strlen(new_path) - 1;
	if (i > 0 && new_path[i] == '/')
		new_path[i] = '\0';
	err = check_dir_access(new_path);
	err = chdir(new_path);
	if (err != 0)
	{
		perror("minishell: cd");
		return (err);
	}
	err = update_env(new_path, env);
	ft_printf("PWD: %s\n", search_env_var(env, "PWD")->value);
	ft_printf("OLDPWD: %s\n", search_env_var(env, "OLDPWD")->value);
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
	char	*cpy_pwd;

	cpy_pwd = ft_calloc(1, sizeof(char));
	getcwd(new_path, PATH_MAX);
	env = search_env_var(env, "PWD");
	cpy_pwd = ft_strdup(env->value);
	if (!cpy_pwd)
	{
		perror("minishell: cd");
		return (1);
	}
	env->value = ft_strdup(new_path);
	if (!env->value)
	{
		perror("minishell: cd");
		free(cpy_pwd);
		return (1);
	}
	env = search_env_var(env, "OLDPWD");
	env->value = ft_strdup(cpy_pwd);
	if (!env->value)
	{
		perror("minishell: cd");
		free(cpy_pwd);
		return (1);
	}
	free(cpy_pwd);
	return (0);
}

static int	no_arg_cd(t_env_lst *env)
{
	t_env_lst	*home;

	home = search_env_var(env, "HOME");
	if (!home || !(home->value))
	{
		ft_cd("/", env);
		return (0);
	}
	ft_cd(home->value, env);
	return (0);
}
