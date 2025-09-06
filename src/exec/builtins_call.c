/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:04 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/03 10:06:23 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "builtins.h"
#include "env.h"

/**
* @brief returns the content of the PATH env var
* @brief as a string. If undefined, returns "." as in "current wd",
* @brief so that executables are only looked for in the cwd.
*/
char	*check_path_exist(t_env_lst *env)
{
	t_env_lst	*var;
	char		*path;

	var = search_env_var(env, "PATH");
	if (!var)
		path = ft_strdup(".");
	else
	{
		path = get_env_val(env, "PATH");
		if (path && ft_strlen(path) == 0)
		{
			free(path);
			path = ft_strdup(".");
		}
	}
	return (path);
}

/**
 * @brief takes a list of possible paths and a cmd, and returns the first
 * possible path that leads to an existing and executable file within the
 * directories listed in `paths`.
 * @return the first correct path if found
 * @return an empty string if no path is found
 * @return NULL in case of error.
 */
char	*find_executable(char	**paths, char *cmd)
{
	size_t	i;
	char	*path;

	i = 0;
	path = NULL;
	while (paths[i])
	{
		path = ft_concat(3, paths[i], "/", cmd);
		if (!path)
			return (NULL);
		else if (access(path, F_OK & X_OK) == 0)
			break ;
		free(path);
		path = NULL;
		++i;
	}
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

int	call_cmd(t_minishell *ms_data, char **cmd)
{
	int			err;

	err = 1;
	if (!cmd[0])
		err = SUCCESS;
	else if (!ft_strncmp(cmd[0], "echo", 5))
		err = ft_echo(cmd, ms_data);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		err = ft_cd(cmd, ms_data);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		err = ft_pwd(cmd, ms_data);
	else if (!ft_strncmp(cmd[0], "export", 7))
		err = ft_export(cmd, ms_data);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		err = ft_unset(cmd, ms_data);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		err = ft_exit(cmd, ms_data);
	else if (!ft_strncmp(cmd[0], "env", 4))
		err = ft_env(cmd, ms_data);
	if (err > 300 && err != ERR_ALLOC)
		err -= 300;
	update_qm(&ms_data->error, err, 0);
	return (err);
}
