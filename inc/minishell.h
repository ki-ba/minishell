/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:02:21 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/30 14:02:24 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* COMMON DEPENDANCIES */

# include "libft.h"
# include "data_structures.h"

/* EXTERNAL DEPENDANCIES */

// # include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

/* MINISHELL MODULES */

# include "lexing.h"
# include "parsing.h"
# include "exec.h"
# include "builtins.h"
# include "env.h"
# include "signals.h"
# include "history.h"
# include "error.h"

/* INITIAL FORMATTING */

char	*trim_cmd(char *cmd);
char	*format_cmd(t_env_lst *env, char *cmd);

/* MAIN FUNCTIONS */

int		handle_line(t_env_lst *env, char cmd[], t_bool *is_exit, int *error);
int		readline_loop(t_env_lst *env_lst);

# ifndef DEBUG
#  define DEBUG FALSE
# endif

# ifndef HERE_DOC_LEN
#  define HERE_DOC_LEN 8
# endif

extern int	g_signal; // sig_atomic_t

#endif
