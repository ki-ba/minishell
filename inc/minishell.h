/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:02:21 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/02 16:47:23 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_structures.h"

/* MS DATA */

void			destroy_ms(t_minishell *ms);

/* INITIAL FORMATTING */

char			*format_cmd(t_minishell *ms, char *cmd);

/* MAIN FUNCTIONS */

void			error_handler(t_minishell *ms);
int				handle_line(t_minishell *ms_data, char cmd[]);
int				readline_loop(t_minishell *minishell_data);

void			print_arr_oneline(char **arr);
void			print_tokens(t_list *tokens);
void			print_exec_lst(t_list *exec_lst);

# ifndef HERE_DOC_LEN
#  define HERE_DOC_LEN 8
# endif

# ifndef DEBUG
#  define DEBUG 0
# endif
#endif
