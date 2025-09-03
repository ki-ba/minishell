/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:17:03 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/03 11:15:18 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "data_structures.h"

# define DOLLAR 0
# define METACHAR 1

/* LEXING */

int				tokenize(t_list **tokens, char *line);

/* LEXING UTILS */
int				check_quotes(char *line);
size_t			count_token_len(char *line);

/* EXPAND */

char			*expand_line(t_minishell *ms, char str[], int option);

/* EXPAND UTILS */

void			join_in_place(char **s1, char *s2);
size_t			get_part_len_dollar(char str[]);
size_t			get_part_len_metachar(char str[]);
// size_t			get_part_len(char str[], int option);

/* EXPAND CHECK */

int				is_metachar(char c);
t_bool			is_inquote(char *str, size_t pos);
t_bool			must_expand(char str[], size_t pos);
int				check_meta_validity(char *str);

/* QUOTES */

void			remove_quotes(void *item);

/* TOKEN */

int				delete_tokens(t_list **tokens, t_token *cur_token);
void			deltoken(void *token);

/* ID TOKEN */
t_token_type	determine_redirect(char token_str[]);
t_bool			determine_option(char token_str[]);
t_bool			determine_pipe(char token_str[]);

#endif
