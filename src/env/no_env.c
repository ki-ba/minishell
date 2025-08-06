/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:15 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/04 14:14:52 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "env.h"
#include <limits.h>

static void	add_pwd(t_env_lst **env_lst)
{
	t_env_lst	*check;
	char		*name;

	name = NULL;
	name = getcwd(name, PATH_MAX);
	env_add_back(env_lst, new_env_entry("?CURRPATH", name));
	check = search_env_var(*env_lst, "PWD");
	if (!check)
		env_add_back(env_lst, new_env_entry("PWD", name));
	free(name);
}

t_env_lst	**empty_env_check(t_env_lst **env_lst)
{
	t_env_lst	*check;

	check = search_env_var(*env_lst, "?CURRPATH");
	if (!check)
		add_pwd(env_lst);
	check = search_env_var(*env_lst, "OLDPWD");
	if (!check)
		env_add_back(env_lst, new_env_entry("OLDPWD", NULL));
	check = search_env_var(*env_lst, "SHLVL");
	if (!check)
		env_add_back(env_lst, new_env_entry("SHLVL", "1"));
	return (env_lst);
}
