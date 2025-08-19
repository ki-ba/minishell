/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:17:03 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/04 14:20:10 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
// #include "libft.h"
// # include <stddef.h>

/* LEXING */

t_token_type	token_type(char val[], t_token_type *last_type, t_bool *cmd_b);
t_token			*token(t_list **tokens, char *token_str, t_bool *cmd_bool);
int				tokenize(t_list **tokens, char *line);

/* LEXING UTILS */
int				check_quotes(char *line);
size_t			count_token_len(char *line);

/* EXPAND */

char			*expand_line(t_env_lst *env, char str[]);

/* EXPAND UTILS */

void			join_in_place(char **s1, char *s2);
size_t			varnamelen(char str[]);
size_t			get_part_len(char str[]);

/* EXPAND CHECK */

int				is_metachar(char c);
t_bool			is_inquote(char *str, size_t pos);
t_bool			must_expand(char str[], size_t pos);
int				check_meta_validity(char *str);

/* QUOTES */

void			remove_quotes(void *item);

/* TOKEN */

void			deltoken(void *token);

/* ID TOKEN */
t_token_type	determine_redirect(char token_str[]);
t_bool			determine_option(char token_str[]);
t_bool			determine_pipe(char token_str[]);
