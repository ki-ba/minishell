/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:46:51 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/04 13:53:29 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/* ENV INIT */

t_env_lst		*create_environment(t_env_lst **env_lst, char *envp[]);
char			**create_env_arr(t_env_lst *env_lst);
void			destroy_env_lst(t_env_lst *env_lst);
t_env_lst		*new_env_entry(char *name, char *value);
void			add_to_env(t_env_lst *env, char *name, char *val, t_bool sh);

/* ENV UTILS */

int				handle_shlvl(t_env_lst *new);
t_env_lst		*create_env_lst(char name[]);
void			env_add_back(t_env_lst **head, t_env_lst *new);
char			*get_env_val(t_env_lst *env, char name[], int sh);
size_t			get_env_size(t_env_lst *env_lst);

/* ENVLIST UTILS */

void			update_qm(t_env_lst *env, int status, int conditionnal);
size_t			envlist_len(t_env_lst *env);
char			**envlist_to_arr(t_env_lst *env_lst);
t_env_lst		*search_env_var(t_env_lst *env, char *var);

/* NO ENV */

t_env_lst		**empty_env_check(t_env_lst **env_lst);

#endif
