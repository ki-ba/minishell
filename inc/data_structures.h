/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:08:47 by kbarru            #+#    #+#             */
/*   Updated: 2025/05/17 15:19:25 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

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

typedef struct s_token
{
	enum e_token_type	type;
	char				*token;

}						t_token;

typedef struct s_exec_lst
{
	char				**cmd;
	struct s_exec_lst	*next;
}						t_exec_lst;

/* storing env as a linked list is simplifies the implementation
 * of functions that modifiy the environment size, i.e unset, export.... */
typedef struct s_env_lst
{
	char				*name;
	char				*value;
	struct s_env_lst	*next;
}						t_env_lst;

#endif
