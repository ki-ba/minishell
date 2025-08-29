/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:02:21 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/29 05:04:17 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_structures.h"

# ifndef DEBUG
#  define DEBUG 0
# endif
/* MS DATA */

void		destroy_ms(t_minishell *ms);

/* INITIAL FORMATTING */

char		*trim_cmd(char *cmd);
char		*format_cmd(t_minishell *ms, char *cmd);

/* MAIN FUNCTIONS */

int			handle_line(t_minishell *ms_data, char cmd[]);
int			readline_loop(t_minishell *minishell_data);

/* DEBUG */ // TODO: REMOVE THESE

t_exec_node	getnode(t_list *exec_lst);
void		print_exec_lst(t_list *exec_lst);

# ifndef HERE_DOC_LEN
#  define HERE_DOC_LEN 8
# endif

#endif
