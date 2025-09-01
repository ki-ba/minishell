/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:49:52 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/29 07:05:09 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "error.h"
#include "env.h"

int	check_dir_access(char *new_path)
{
	if (access(new_path, R_OK | X_OK))
		return (ERR_ARGS);
	return (SUCCESS);
}

void	skip_slashes(char *str)
{
	size_t	i;

	i = ft_strlen(str);
	while (i > 0 && str[i - 1] == '/')
	{
		str[i - 1] = '\0';
		--i;
	}
}

int	update_env(char *new_path, t_minishell *ms_data)
{
	t_env_lst	*env_var;

	env_var = search_env_var(ms_data->env, "OLDPWD");
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ms_data->cur_wd;
	}
	else
		free (ms_data->cur_wd);
	ms_data->cur_wd = ft_strdup(new_path);
	if (!ms_data->cur_wd)
		return (ERR_ALLOC);
	env_var = search_env_var(ms_data->env, "PWD");
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(ms_data->cur_wd);
		if (!env_var->value)
			return (ERR_ALLOC);
	}
	return (SUCCESS);
}

char	*setup_path0(char **path)
{
	char	*tmp;

	if (path[0][0] != '\0' && path[0][ft_strlen(path[0]) - 1] == '/' &&
		path[2][0] == '/')
		tmp = ft_strdup(path[0]);
	else if (path[0][0] == '\0' || path[0][ft_strlen(path[0]) - 1] == '/')
		tmp = ft_concat(2, path[0], path[2]);
	else
		tmp = ft_concat(3, path[0], "/", path[2]);
	return (tmp);
}
