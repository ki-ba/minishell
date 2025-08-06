/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:33:19 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/04 14:11:43 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "error.h"
#include "env.h"

/**
 * @brief print the current directory
 * @param cmd is the command, with its options and arguments
 * @return 0 is the directory could be printed, non-zero otherwise
 */
int	ft_pwd(char **cmd, t_env_lst *env)
{
	char	*path;

	(void)cmd;
	path = get_env_val(env, "CURRPATH", 1);
	printf("%s\n", path);
	return (SUCCESS);
}
