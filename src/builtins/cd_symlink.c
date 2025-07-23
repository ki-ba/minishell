/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_symlink.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:22:39 by mlouis            #+#    #+#             */
/*   Updated: 2025/07/23 20:42:15 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shortcut_path(char **path, ssize_t i, char *cmd);
static int	normal_path(char **path, ssize_t i);
static int	prev_dir_shortcut(char **path, ssize_t i);

int	getsymlink_helper(char **path_parts, char *cmd, size_t len)
{
	ssize_t	i;
	int		err;

	i = find_char(path_parts[1], '/') + 1;
	if (i == 0)
		i = len;
	path_parts[2] = ft_substr(path_parts[1], 0, i);
	if (!path_parts[2])
	{
		free(path_parts[0]);
		free(path_parts[1]);
		return (ERR_ALLOC);
	}
	if (path_parts[2][0] == '.')
		err = shortcut_path(path_parts, i, cmd);
	else
		err = normal_path(path_parts, i);
	return (SUCCESS);
}

int	setup_path_parts(char **path_parts, char *cmd, t_env_lst *env)
{
	if (cmd[0] != '/')
		path_parts[0] = ft_strdup(get_env_val(env, "PWD", 1));
	else
		path_parts[0] = ft_strdup("");
	if (!path_parts[0])
		return (ERR_ALLOC);
	path_parts[1] = ft_strdup(cmd);
	if (!path_parts[1])
	{
		free(path_parts[0]);
		return (ERR_ALLOC);
	}
	return (SUCCESS);
}

static int	shortcut_path(char **path, ssize_t i, char *cmd)
{
	ssize_t	j;
	int		err;

	if (ft_strlen(path[0]) > 1 && path[0][ft_strlen(path[0]) - 1] == '/')
		path[0][ft_strlen(path[0]) - 1] = '\0';
	j = find_char_end(path[0], '/');
	if (j == -1)
		j = ft_strlen(cmd);
	err = SUCCESS;
	if (!ft_strncmp(path[2], "..", 3) || !ft_strncmp(path[2], "../", 4))
		err = prev_dir_shortcut(path, j);
	free(path[2]);
	if (err)
		return (ERR_ALLOC);
	path[2] = path[1];
	path[1] = ft_substr(path[2], i, ft_strlen(path[2]));
	free(path[2]);
	if (!path[1])
	{
		free(path[0]);
		return (ERR_ALLOC);
	}
	return (SUCCESS);
}

static int	prev_dir_shortcut(char **path, ssize_t i)
{
	char	*tmp;

	tmp = ft_substr(path[0], 0, i);
	free(path[0]);
	if (!tmp)
	{
		free(path[2]);
		return (ERR_ALLOC);
	}
	path[0] = ft_strdup(tmp);
	free(tmp);
	if (!path[0])
	{
		free(path[2]);
		return (ERR_ALLOC);
	}
	return (SUCCESS);
}

static int	normal_path(char **path, ssize_t i)
{
	char	*tmp;

	if (path[0][0] == '\0' || path[0][ft_strlen(path[0]) - 1] == '/')
		tmp = ft_concat(2, path[0], path[2]);
	else
		tmp = ft_concat(3, path[0], "/", path[2]);
	free(path[2]);
	free(path[0]);
	if (!tmp)
		return (ERR_ALLOC);
	path[0] = ft_strdup(tmp);
	free(tmp);
	if (!path[0])
		return (ERR_ALLOC);
	path[2] = path[1];
	path[1] = ft_substr(path[2], i, ft_strlen(path[2]));
	free(path[2]);
	if (!path[1])
	{
		free(path[0]);
		return (ERR_ALLOC);
	}
	return (SUCCESS);
}
