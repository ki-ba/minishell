/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:52:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/06 16:33:49 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "data_structures.h"
#include "exec.h"
#include "minishell.h"
#include <sys/stat.h>

int	sclose(int fd)
{
	if (fd <= 2)
		return (1);
	else
		return (close(fd));
}

int	apply_redirections(t_list **cur_node)
{
	t_exec_node	*exe;
	int			err;

	err = 0;
	exe = (t_exec_node *)(*cur_node)->content;
	if (exe->io[1] != STDOUT_FILENO)
		err = dup2(exe->io[1], STDOUT_FILENO);
	if (err >= 0 && exe->io[0] != STDIN_FILENO)
		err = dup2(exe->io[0], STDIN_FILENO);
	sclose (exe->io[0]);
	sclose (exe->io[1]);
	return (err);
}

/**
* @brief returns the first path found to a given executable.
* @brief looks first in PATH env var, then in current directory.
* @brief if `cmd` contains a / (its a relative / absolute path),
* @brief do not look in PATH and simply return the path which was given.
* @brief
*/
char	*path_to_cmd(char *cmd[], t_env_lst *env)
{
	char	**paths;
	char	*path;

	if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])))
		path = ft_strdup(cmd[0]);
	else
	{
		path = check_path_exist(env);
		if (!path)
			return (NULL);
		paths = ft_split(path, ':');
		if (!paths)
		{
			free(path);
			return (NULL);
		}
		free(path);
		path = find_executable(paths, cmd[0]);
		ft_free_arr(paths);
	}
	return (path);
}

int	define_error(char path[])
{
	int			err;
	struct stat	fi;

	if (!path)
		return (ERR_ALLOC);
	stat(path, &fi);
	if (access(path, F_OK))
		err = 127;
	else if (S_ISDIR(fi.st_mode) || access(path, X_OK))
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", path);
		err = 126;
	}
	else
		err = 0;
	return (err);
}
