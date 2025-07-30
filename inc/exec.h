/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:38:13 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/30 12:45:34 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "data_structures.h"
# include <stddef.h>
# include "libft.h"

/* EXECUTION */

int		wait_processes(pid_t pid, int err);
int		start_execution(t_list *exec, t_env_lst *env, t_bool *is_exit);
int		interpret_line(char *cmd, t_env_lst *env_lst, t_bool *is_exit);

/* EXEC UTILS */

void	failed_file_handler(t_list **exec, t_env_lst **env, int pipe_fd[2]);
pid_t	dup_n_fork(t_list **exec, t_list **cur, t_env_lst **env, int *nxt_pip);
char	*path_to_cmd(char *cmd[], t_env_lst *env);
int		define_error(char path[], t_env_lst *env);
void	set_child_io(t_list **exe_ls, t_exec_node *exe, int *nxt_pip, int p[2]);

/* BUILTINS CALL */

char	*check_path_exist(t_env_lst *env);
char	*find_path(char *cmd, t_env_lst *env);
t_bool	is_builtin(char **cmd);
int		call_cmd(char **cmd, t_env_lst *env);

/* EXECUTE PIPELINE */

int		try_exec(t_list **exec, char **cmd, t_env_lst *env);
void	exec_child(t_list **cur, t_env_lst **env, int *next_pipe, int pipe[2]);
void	exec_parent(t_exec_node *exe, int *nxt_pipe, int pipe[2]);
int		exec_unique_cmd(t_list **exec_lst, t_env_lst *env);
pid_t	exec_pipeline(t_list **exec_lst, t_env_lst **env);

#endif
