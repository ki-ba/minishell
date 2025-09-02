/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:02:21 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/02 10:19:40 by mlouis           ###   ########.fr       */
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

void			destroy_ms(t_minishell *ms);

/* INITIAL FORMATTING */

char			*format_cmd(t_minishell *ms, char *cmd);

/* MAIN FUNCTIONS */

void			error_handler(t_minishell *ms);
int				handle_line(t_minishell *ms_data, char cmd[]);
int				readline_loop(t_minishell *minishell_data);

# ifndef HERE_DOC_LEN
#  define HERE_DOC_LEN 8
# endif

#endif
