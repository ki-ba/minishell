/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:41:42 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/29 00:59:32 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "error.h"
#include "env.h"

static int	no_arg_cd(char **cmd, t_minishell *ms_data);
static int	change_dir(char **cmd, t_minishell *ms_data);
static char	*getsymlink(char *cmd, t_minishell *ms_data);

/** @brief if relative => check access from end to start */
/** @param cmd[0] is the cmd (here cd) */
/** @param cmd[1] is the new path */
/** @param cmd[2] should be NULL */
/** @return 0 on success or a non-zero int on failure */
int	ft_cd(char **cmd, t_minishell *ms_data)
{
	if (cmd[1] != NULL && cmd[2] != NULL)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (ERR_ARGS);
	}
	if (cmd[1] == NULL)
		return (no_arg_cd(cmd, ms_data));
	return (change_dir(cmd, ms_data));
}

static int	change_dir(char **cmd, t_minishell *ms_data)
{
	size_t		i;
	int			err;
	char		*path;

	path = NULL;
	if (cmd[1][0] == '\0')
		return (SUCCESS);
	i = ft_strlen(cmd[1]) - 1;
	while (i > 0 && cmd[1][i] == '/')
	{
		cmd[1][i] = '\0';
		--i;
	}
	path = getsymlink(cmd[1], ms_data);
	if (!path)
		return (ERR_ALLOC);
	err = check_dir_access(path);
	if (err == SUCCESS)
		err = chdir(path);
	if (err)
	{
		free(path);
		perror("minishell: cd");
		return (ERR_ARGS);
	}
	if (err == SUCCESS)
		err = update_env(path, ms_data);
	free(path);
	return (err);
}

static char	*getsymlink(char *cmd, t_minishell *ms_data)
{
	char	*path_parts[3];
	int		err;
	size_t	len;

	err = setup_path_parts(path_parts, cmd, ms_data);
	if (err)
		return (NULL);
	len = ft_strlen(cmd);
	while (path_parts[1][0] != '\0')
	{
		err = getsymlink_helper(path_parts, cmd, len);
		if (err)
		{
			if (path_parts[0])
				free(path_parts[0]);
			if (path_parts[1])
				free(path_parts[1]);
			if (path_parts[2])
				free(path_parts[2]);
			return (NULL);
		}
	}
	if (path_parts[1])
		free(path_parts[1]);
	// if (path_parts[0][0] == '\0')
	// {
	// 	free(path_parts[0]);
	// 	path_parts[0] = ft_strdup("/");
	// 	if (!path_parts[0])
	// 		return (NULL);
	// }
	return (path_parts[0]);
}

static int	no_arg_cd(char **cmd, t_minishell *ms_data)
{
	t_env_lst	*home;
	int			err;

	err = 0;
	home = search_env_var(ms_data->env, "HOME");
	if (!home || !home->value)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (ERR_ARGS);
	}
	else
	{
		cmd[1] = ft_strdup(home->value);
		if (!cmd[1])
			return (ERR_ALLOC);
	}
	err = change_dir(cmd, ms_data);
	free(cmd[1]);
	cmd[1] = NULL;
	return (err);
}
