/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:04 by mlouis            #+#    #+#             */
/*   Updated: 2025/07/30 14:09:05 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path_exist(t_env_lst *env)
{
	t_env_lst	*var;
	char		*path;

	var = search_env_var(env, "PATH");
	if (!var)
		path = ft_strdup(".");
	else
	{
		path = ft_strdup(get_env_val(env, "PATH", 0));
		if (!path)
			path = ft_strdup(".");
	}
	return (path);
}

char	*find_path(char *cmd, t_env_lst *env)
{
	char	**paths;
	char	*path;
	size_t	i;

	path = check_path_exist(env);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	if (path)
		free(path);
	i = 0;
	path = NULL;
	while (paths[i])
	{
		path = ft_concat(3, paths[i], "/", cmd);
		if (!path || !access(path, F_OK & X_OK))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	ft_free_arr(paths);
	if (!path)
		return (ft_strdup(""));
	return (path);
}

t_bool	is_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
		return (1);
	if (ft_strncmp(cmd[0], "echo", 5))
		if (ft_strncmp(cmd[0], "cd", 3))
			if (ft_strncmp(cmd[0], "pwd", 4))
				if (ft_strncmp(cmd[0], "export", 7))
					if (ft_strncmp(cmd[0], "unset", 6))
						if (ft_strncmp(cmd[0], "exit", 5))
							return (!ft_strncmp(cmd[0], "env", 4));
	return (TRUE);
}

int	call_cmd(char **cmd, t_env_lst *env)
{
	int			err;

	err = 1;
	if (!cmd[0])
		err = SUCCESS;
	else if (!ft_strncmp(cmd[0], "echo", 5))
		err = ft_echo(cmd, env);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		err = ft_cd(cmd, env);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		err = ft_pwd(cmd, env);
	else if (!ft_strncmp(cmd[0], "export", 7))
		err = ft_export(cmd, env);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		err = ft_unset(cmd, env);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		err = ft_exit(cmd, env);
	else if (!ft_strncmp(cmd[0], "env", 4))
		err = ft_env(cmd, env);
	if (err > 300 && err != ERR_ALLOC)
		err -= 300;
	update_qm(env, err, 0);
	return (err);
}
