/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:03:16 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/01 13:19:29 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "env.h"
#include "error.h"
#include <linux/limits.h>

static int	get_cur_wd(t_minishell *ms)
{
	char	*env_cwd;

	env_cwd = getenv("PWD");
	if (env_cwd)
		ms->cur_wd = ft_strdup(env_cwd);
	else
		ms->cur_wd = getcwd(ms->cur_wd, PATH_MAX);
	if (!ms->cur_wd)
		return (ERR_ALLOC);
	return (SUCCESS);
}

t_env_lst	*create_environment(t_minishell *ms_data, char *envp[])
{
	size_t		i;
	t_env_lst	*new;

	i = 0;
	if (get_cur_wd(ms_data))
		return (NULL);
	while (envp[i])
	{
		new = create_env_lst(envp[i]);
		env_add_back(&ms_data->env, new);
		if (!new)
		{
			destroy_env_lst(&ms_data->env);
			return (NULL);
		}
		++i;
	}
	empty_env_check(ms_data);
	return (ms_data->env);
}

t_env_lst	*new_env_entry(char *name, char *value)
{
	t_env_lst	*new;

	new = ft_calloc(1, sizeof(t_env_lst));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}
