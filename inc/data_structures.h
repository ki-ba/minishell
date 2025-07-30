/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:08:47 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/30 12:22:19 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

# include <stddef.h>

/* note : a TOKEN_FILE can only be after a redirection.
 * in other cases, it is considered a TOKEN_STR,
 * even when it is supposed to refer to a file
 * (i.e the arg after `cat` command) */
typedef enum e_token_type
{
	TOKEN_CMD = 0,
	TOKEN_OPT,
	TOKEN_STR,
	TOKEN_PIPE,
	TOKEN_REDIRECT,
	TOKEN_FILE,
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
	char				*(filename[2]); // each can be NULL or a filename
	int					io[2]; // both can be either 0, 1, 2, or 3 (for file)
	int					oflags[2];
	int					file_exist; //check if file existed before > or >>
	int					status;
}						t_exec_node;

/* storing env as a linked list is simplifies the implementation
 * of functions that modifiy the environment size, i.e unset, export.... */
typedef struct s_env_lst
{
	char				*name;
	char				*value;
	struct s_env_lst	*next;
}						t_env_lst;

#endif
