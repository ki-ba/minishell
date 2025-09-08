/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:38:13 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/02 10:07:54 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/* EXECUTION */

int		interpret_line(t_minishell *ms, char *cmd);

/* EXEC UTILS */

char	*path_to_cmd(char *cmd[], t_env_lst *env);
int		define_error(char path[]);
int		sclose(int fd);
pid_t	dup_n_fork(t_minishell *ms, t_list **cur);
int		clean_exit_child(t_minishell *ms, t_list **node, char **cmd);

/* BUILTINS CALL */

char	*check_path_exist(t_env_lst *env);
char	*find_executable(char **paths, char *cmd);
t_bool	is_builtin(char **cmd);
int		call_cmd(t_minishell *ms, char **cmd);

/* EXECUTE PIPELINE */

int		try_exec(t_minishell *ms, t_list **exec, char **cmd);
int		exec_unique_cmd(t_minishell *ms, t_list **exec_lst);
pid_t	exec_pipeline(t_minishell *ms);

#endif
