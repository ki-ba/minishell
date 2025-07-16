#include "minishell.h"
#include "builtins.h"
#include "error.h"
#include <limits.h>

static int	no_arg_cd(char **cmd, t_env_lst *env);
static int	update_env(char *new_path, t_env_lst *env);
static int	check_dir_access(char *new_path);
static int	change_dir(char **cmd, t_env_lst *env);
static char	*getsymlink(char *cmd, char *path, t_env_lst *env);

/** @brief if relative => check access from end to start */
/** @param cmd[0] is the cmd (here cd) */
/** @param cmd[1] is the new path */
/** @param cmd[2] should be NULL */
/** @return 0 on success or a non-zero int on failure */
int	ft_cd(char **cmd, t_env_lst *env)
{
	if (cmd[1] != NULL && cmd[2] != NULL)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (ERR_ARGS);
	}
	if (cmd[1] == NULL)
		return (no_arg_cd(cmd, env));
	return (change_dir(cmd, env));
}

static int	change_dir(char **cmd, t_env_lst *env)
{
	size_t		i;
	int			err;
	char		*path;

	path = NULL;
	if (cmd[1][0] == '\0')
		return (SUCCESS);
	i = ft_strlen(cmd[1]) - 1;
	if (i > 0 && cmd[1][i] == '/')
		cmd[1][i] = '\0';
	err = check_dir_access(cmd[1]);
	if (err != 0)
		return (ERR_ARGS);
	path = getsymlink(cmd[1], path, env);
	if (!path)
		return (ERR_ALLOC);
	err = chdir(path);
	if (err != 0)
		return (ERR_ARGS);
	err = update_env(path, env);
	free(path);
	return (err);
}

static char	*getsymlink(char *cmd, char *path, t_env_lst *env)
{
	char	*curr;
	char	*sub;
	char	*rest;
	char	*tmp;
	ssize_t	j;
	ssize_t	k;
	size_t	len;

	if (cmd[0] != '/')
		curr = ft_strdup(get_env_val(env, "PWD", 1));
	else
		curr = ft_strdup("");
	len = ft_strlen(cmd);
	rest = ft_strdup(cmd);
	while (rest[0] != '\0')
	{
		j = find_char(rest, '/') + 1;
		if (j == 0)
			j = len;
		sub = ft_substr(rest, 0, j);
		if (sub[0] == '.')
		{
			if (ft_strlen(curr) > 1 && curr[ft_strlen(curr) - 1] == '/')
				curr[ft_strlen(curr) - 1] = '\0';
			k = find_char_end(curr, '/');
			if (k == -1)
				k = len;;
			if (!ft_strncmp(sub, "..", 3) || !ft_strncmp(sub, "../", 4))
			{
				tmp = ft_substr(curr, 0, k);
				free(curr);
				curr = ft_strdup(tmp);
				free(tmp);
			}
			free(sub);
			sub = rest;
			rest = ft_substr(sub, j, ft_strlen(sub));
			free(sub);
		}
		else
		{
			if (curr[0] == '\0' || curr[ft_strlen(curr) - 1] == '/')
				tmp = ft_concat(2, curr, sub);
			else
				tmp = ft_concat(3, curr, "/", sub);
			free(sub);
			free(curr);
			curr = ft_strdup(tmp);
			free(tmp);
			sub = rest;
			rest = ft_substr(sub, j, ft_strlen(sub));
			free(sub);
		}
	}
	if (rest)
		free(rest);
	if (curr[0] == '\0')
	{
		free(curr);
		curr = ft_strdup("/");
	}
	path = ft_strdup(curr);
	free(curr);
	return (path);
}

static int	check_dir_access(char *new_path)
{
	char	*full_path;
	char	*sub;
	char	*tmp;
	size_t	i;
	size_t	j;
	int		err;

	i = 0;
	full_path = NULL;
	sub = NULL;
	while (new_path[i] != '\0')
	{
		j = i + 1;
		while (new_path[j - 1] != '/' && new_path[j] != '\0')
			j++;
		sub = ft_substr(new_path, i, j - i);
		tmp = full_path;
		full_path = ft_concat(2, tmp, sub);
		free(tmp);
		free(sub);
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
	t_env_lst	*tmp1;
	t_env_lst	*tmp2;

	tmp1 = search_env_var(env, "?PWD");
	tmp2 = search_env_var(env, "?OLDPWD");
	free(tmp2->value);
	tmp2->value = ft_strdup(tmp1->value);
	if (!tmp2->value)
	{
		perror("minishell: cd");
		return (ERR_ALLOC);
	}
	free(tmp1->value);
	tmp1->value = ft_strdup(new_path);
	if (!tmp1->value)
	{
		perror("minishell: cd");
		return (ERR_ALLOC);
	}
	tmp2 = search_env_var(env, "PWD");
	if (tmp2)
	{
		free(tmp2->value);
		tmp2->value = ft_strdup(tmp1->value);
	}
	tmp1 = search_env_var(env, "?OLDPWD");
	tmp2 = search_env_var(env, "OLDPWD");
	if (tmp2)
	{
		free(tmp2->value);
		tmp2->value = ft_strdup(tmp1->value);
	}
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
	change_dir(cmd, env);
	free(cmd[1]);
	cmd[1] = NULL;
	return (0);
}
