/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:02:41 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/19 16:42:07 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "parsing.h"
#include "error.h"

// NOTE : REDIRECTIONS TAKE OVER PIPES. This means if the i/o of a command
// is supposed to be piped, but a redirection is encountered, the pipe fd
// should be closed and the i/o be replaced by the redirection.

static int	define_open_flags(t_token_type type)
{
	if (type == T_REDIR_OUT)
		return (O_CREAT | O_TRUNC | O_WRONLY);
	else if (type == T_APPEND)
		return (O_CREAT | O_APPEND | O_WRONLY);
	else
		return (O_RDONLY);
}

static int	def_redir_type(t_token_type type)
{
	if (type == T_REDIR_IN || type == T_HD)
		return (INFILE);
	else if (type == T_REDIR_OUT || type == T_APPEND)
		return (OUTFILE);
	return (-1);
}

static int	handle_file(t_exec_node *node, t_token *token, t_token_type redir)
{
	int	oflags;

	if (!node || !token)
		return (ERR_ALLOC);
	if (redir == T_HD)
		node->io[0] = read_input(token->token);
	else if (node->status == 0)
	{
		oflags = define_open_flags(redir);
		node->io[def_redir_type(redir)] = open(token->token, oflags, 0644);
		if (node->io[redir] < 0)
			perror("open");
	}
	return (node->io[redir] < 0);
}

/**
 * handles current TOKEN_CMD.
 *	adds the current command or parameter to the cmd array.
 **/
static int	handle_cmd(t_exec_node *node, t_token *token, t_list **exec_list)
{
	char	**old_arr;

	if (!node || !token || !exec_list)
		return (ERR_ALLOC);
	old_arr = node->cmd;
	node->cmd = add_to_array(node->cmd, token->token);
	if (!node->cmd)
	{
		if (old_arr)
			ft_free_arr(old_arr);
		ft_lstclear(exec_list, del_exec_node);
		return (ERR_ALLOC);
	}
	return (SUCCESS);
}

/**
 * @brief handles current PIPE_CMD, or the first token of the line.
 * @brief creates a new exec_node which data (i/o, filename, cmd ...)
 * @brief will be filled by other handler functions.
 **/
static int	new_node(t_list **exec_lst)
{
	t_list		*new_list_node;
	t_exec_node	*new_node;

	new_node = create_exec_node();
	new_list_node = ft_lstnew(new_node);
	if (!new_node || !new_list_node)
	{
		ft_multifree(2, 0, new_node, new_list_node);
		return (ERR_ALLOC);
	}
	ft_lstadd_back(exec_lst, new_list_node);
	return (SUCCESS);
}

/**
* Parse the token list and create a process list with correct infiles,
* outfiles, argv and environments.
*/
int	parse_tokens(t_minishell *ms, t_list *tokens)
{
	t_token			*token;
	t_exec_node		*node;
	t_token_type	redir_type;
	int				status;

	status = 0;
	if (new_node(&ms->exec_lst))
		return (ERR_ALLOC);
	while (tokens && status != ERR_ALLOC)
	{
		node = ft_lstlast(ms->exec_lst)->content;
		token = (t_token *)(tokens)->content;
		if (token->type == T_PIPE)
			status = new_node(&ms->exec_lst);
		else if (token->type >= T_CMD && token->type <= T_STR)
			status = handle_cmd(node, token, &ms->exec_lst);
		else if (token->type >= T_REDIR_IN && token->type <= T_HD)
			redir_type = token->type;
		else if (token->type == T_FILE)
			status = handle_file(node, token, redir_type);
		if (node && node->status && status != 0)
			node->status = status;
		tokens = tokens->next;
	}
	return (status);
}
