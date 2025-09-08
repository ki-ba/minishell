/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:46:51 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/06 13:31:34 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/* ENV INIT */

t_env_lst		*create_environment(t_minishell *ms_data, char *envp[]);
t_env_lst		*new_env_entry(char *name, char *value);

/* ENV UTILS */

t_env_lst		*create_env_lst(t_minishell *ms_data, char name[]);
void			env_add_back(t_env_lst **head, t_env_lst *new);
char			*get_env_val(t_env_lst *env, char name[]);
size_t			envlist_len(t_env_lst *env);

/* ENVLIST UTILS */

void			update_qm(t_minishell *ms, int status, int conditionnal);
char			**envlist_to_arr(t_env_lst *env_lst);
t_env_lst		*search_env_var(t_env_lst *env, char *var);
void			del_env_entry(t_env_lst *env_entry);
void			destroy_env_lst(t_env_lst **env_lst);

/* NO ENV */

t_env_lst		**empty_env_check(t_minishell *ms_data);

#endif
