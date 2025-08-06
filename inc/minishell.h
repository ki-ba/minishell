/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:02:21 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/04 15:28:54 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_structures.h"

/* INITIAL FORMATTING */

char	*trim_cmd(char *cmd);
char	*format_cmd(t_env_lst *env, char *cmd);

/* MAIN FUNCTIONS */

int		handle_line(t_env_lst *env, char cmd[], t_bool *is_exit, int *error);
int		readline_loop(t_env_lst *env_lst);

# ifndef HERE_DOC_LEN
#  define HERE_DOC_LEN 8
# endif

#endif
