/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_symlink.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:22:39 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/02 10:35:52 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "builtins.h"

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
	if (!ft_strncmp(path_parts[2], "..", 3)
		|| !ft_strncmp(path_parts[2], "../", 4)
		|| !ft_strncmp(path_parts[2], ".", 2)
		|| !ft_strncmp(path_parts[2], "./", 3))
	{
		err = shortcut_path(path_parts, i, cmd);
		return (err);
	}
	err = normal_path(path_parts, i);
	return (err);
}

int	setup_path_parts(char **path_parts, char *cmd, t_minishell *ms_data)
{
	if (cmd[0] != '/')
		path_parts[0] = ft_strdup(ms_data->cur_wd);
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
	path_parts[2] = NULL;
	return (SUCCESS);
}

static int	shortcut_path(char **path, ssize_t i, char *cmd)
{
	ssize_t	j;
	int		err;

	skip_slashes(path[0]);
	j = find_char_end(path[0], '/');
	if (j == -1)
		j = ft_strlen(cmd);
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

	if (!ft_strncmp(path[2], "..", 3) || !ft_strncmp(path[2], "../", 4))
	{
		tmp = ft_substr(path[0], 0, i);
		free(path[0]);
		if (!tmp)
		{
			free(path[1]);
			return (ERR_ALLOC);
		}
		path[0] = ft_strdup(tmp);
		free(tmp);
		if (!path[0])
		{
			free(path[1]);
			return (ERR_ALLOC);
		}
	}
	return (SUCCESS);
}

static int	normal_path(char **path, ssize_t i)
{
	char	*tmp;

	tmp = setup_path0(path);
	free(path[2]);
	free(path[0]);
	if (!tmp)
	{
		free(path[1]);
		return (ERR_ALLOC);
	}
	path[0] = ft_strdup(tmp);
	free(tmp);
	path[2] = path[1];
	path[1] = ft_substr(path[2], i, ft_strlen(path[2]));
	free(path[2]);
	if (!path[1] || !path[0])
	{
		free(path[0]);
		free(path[1]);
		return (ERR_ALLOC);
	}
	return (SUCCESS);
}
