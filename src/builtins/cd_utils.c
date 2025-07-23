/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:49:52 by mlouis            #+#    #+#             */
/*   Updated: 2025/07/23 20:41:22 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_sys(t_env_lst **env_v, char *new_path, t_env_lst *env);

int	check_dir_access(char *new_path)
{
	int	err;

	err = access(new_path, R_OK | X_OK);
	if (err != 0)
		perror("minishell: cd");
	return (err);
}

int	update_env(char *new_path, t_env_lst *env)
{
	t_env_lst	*env_vars[2];

	if (update_env_sys(env_vars, new_path, env))
		return (ERR_ALLOC);
	env_vars[1] = search_env_var(env, "PWD");
	if (env_vars[1])
	{
		free(env_vars[1]->value);
		env_vars[1]->value = ft_strdup(env_vars[0]->value);
		if (!env_vars[1]->value)
			return (ERR_ALLOC);
	}
	env_vars[0] = search_env_var(env, "?OLDPWD");
	env_vars[1] = search_env_var(env, "OLDPWD");
	if (env_vars[1])
	{
		free(env_vars[1]->value);
		env_vars[1]->value = ft_strdup(env_vars[0]->value);
		if (!env_vars[1]->value)
			return (ERR_ALLOC);
	}
	return (SUCCESS);
}

static int	update_env_sys(t_env_lst **env_v, char *new_path, t_env_lst *env)
{
	env_v[0] = search_env_var(env, "?PWD");
	env_v[1] = search_env_var(env, "?OLDPWD");
	free(env_v[1]->value);
	env_v[1]->value = ft_strdup(env_v[0]->value);
	if (!env_v[1]->value)
		return (ERR_ALLOC);
	free(env_v[0]->value);
	env_v[0]->value = ft_strdup(new_path);
	if (!env_v[0]->value)
		return (ERR_ALLOC);
	return (SUCCESS);
}
