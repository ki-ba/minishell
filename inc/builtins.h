/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:39:50 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/29 06:59:21 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "data_structures.h"

/* CD */

int			ft_cd(char **cmd, t_minishell *ms_data);
int			getsymlink_helper(char **path_parts, char *cmd, size_t len);
int			setup_path_parts(char **path_parts, char *cmd, t_minishell *ms);
int			update_env(char *new_path, t_minishell *ms_data);
int			check_dir_access(char *new_path);
void		skip_slashes(char *str);
char		*setup_path0(char **path);

/* ECHO */

int			ft_echo(char **cmd, t_minishell *ms_data);

/* PWD */

int			ft_pwd(char **cmd, t_minishell *ms_data);

/* EXPORT */

int			ft_export(char **cmd, t_minishell *ms_data);
t_env_lst	*dup_env(t_env_lst *env);
t_env_lst	*sort_env_var(t_env_lst *env);

/* UNSET */

int			ft_unset(char **cmd, t_minishell *ms_data);

/* ENV */

int			ft_env(char **cmd, t_minishell *ms_data);
int			check_name_validity(char *name);

/* EXIT */
int			ft_exit(char **cmd, t_minishell *ms_data);
int			is_correct_exit(char *cmd[]);

#endif
