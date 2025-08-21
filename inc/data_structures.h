/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:08:47 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/21 12:45:40 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

// # include <stddef.h>

typedef struct s_list	t_list;
/* note : a TOKEN_FILE can only be after a redirection.
 * in other cases, it is considered a TOKEN_STR,
 * even when it is supposed to refer to a file
 * (i.e the arg after `cat` command) */
typedef enum e_token_type
{
	T_CMD = 1,
	T_OPT,
	T_STR,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HD,
	T_FILE
}	t_token_type;

typedef enum e_redir
{
	INFILE,
	OUTFILE,
}	t_redir;

/**
 * token extracted from a list.
 * has a type (see e_token_type)
 * and a value string.
 */
typedef struct s_token
{
	enum e_token_type	type;
	char				*token;

}						t_token;

/**
 * list of commands to execute.
 * Created by the parsing part of the project to be interpreted by
 * execution part.
 */
typedef struct s_exec_node
{
	char				**cmd;
	int					io[2];
	int					status;
}						t_exec_node;

typedef struct s_env_lst
{
	char				*name;
	char				*value;
	struct s_env_lst	*next;
}						t_env_lst;

typedef struct s_minishell
{
	char		*last_cmd;
	char		*cur_wd;
	t_env_lst	*env;
	t_list		*exec_lst;
	int			is_exit;
	int			error;
}	t_minishell;
#endif
