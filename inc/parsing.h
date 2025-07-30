/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:29:30 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/30 12:46:23 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "data_structures.h"

/* PARSING */

t_list		*parse_tokens(t_list *tokens);

/* PARSING UTILS */

char		**add_to_array(char **arr, char *str);
int			check_parsing(char str[]);
int			process_tokens(t_list *tokens);

/* EXEC NODE */

t_exec_node	*create_exec_node(void);
void		del_exec_node(void *node);
void		ft_lstclear_but(t_list **lst, void (*f)(void *), t_list *item);

/* DOUBLE INPUT REDIR */

int			ft_max(int a, int b);
int			rl_help(void);
int			read_input(char *del);

#endif
