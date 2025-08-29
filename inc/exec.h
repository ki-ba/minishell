/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:38:13 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/29 06:59:50 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/* EXECUTION */

int		wait_processes(pid_t pid, int err);
int		start_execution(t_minishell *ms);
int		interpret_line(t_minishell *ms, char *cmd);

/* EXEC UTILS */

pid_t	dup_n_fork(t_minishell *ms, t_list **cur);
char	*path_to_cmd(char *cmd[], t_env_lst *env);
int		define_error(char path[], t_env_lst *env);
void	set_child_io(t_minishell *ms, t_list **cur, int pipe_fd[2]);
int		sclose(int fd);

/* BUILTINS CALL */

char	*check_path_exist(t_env_lst *env);
char	*find_path(char *cmd, t_env_lst *env);
t_bool	is_builtin(char **cmd);
int		call_cmd(t_minishell *ms, char **cmd);

/* EXECUTE PIPELINE */

int		try_exec(t_minishell *ms, t_list **exec, char **cmd);
int		exec_unique_cmd(t_minishell *ms, t_list **exec_lst);
pid_t	exec_pipeline(t_minishell *ms);

#endif
