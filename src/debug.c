#include "minishell.h"

void	display_token(t_token *token)
{
	char			token_type[10];
	t_token_type	type_int;

	type_int = token->type;
	if (token->type == TOKEN_CMD)
		ft_strlcpy(token_type, "COMMAND", 10);
	else if (token->type == TOKEN_OPT)
		ft_strlcpy(token_type, "OPTION", 10);
	else if (type_int == TOKEN_STR)
		ft_strlcpy(token_type, "STRING", 10);
	else if (type_int == TOKEN_PIPE)
		ft_strlcpy(token_type, "PIPE", 10);
	else if (type_int == TOKEN_REDIRECT)
		ft_strlcpy(token_type, "REDIRECT", 10);
	else if (type_int == TOKEN_FILE)
		ft_strlcpy(token_type, "FILE", 10);
	else
		ft_strlcpy(token_type, "UNKNOWN", 10);
	ft_printf("\n_token %p : %s\n[%s]\n\n_", token, token_type, token->token);
}

void	print_token_list(t_list *tokens)
{
	t_list	*current;

	current = tokens;
	while (current)
	{
		display_token(current->content);
		current = current->next;
	}
}

char	*summarize_lexing(t_list *tokens)
{
	t_list	*current;
	t_token	*token;
	char	*str;

	str = ft_calloc(1, sizeof(char));
	current = tokens;
	while (current)
	{
		token = (t_token *)current->content;
		str = ft_strjoin(str, ft_itoa(token->type));
		current = current->next;
	}
	str = ft_strjoin(str, ";");
	return (str);
}

static void	print_cmd(char *cmd[])
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		ft_printf("%s ", cmd[i]);
	}
	ft_printf("\n");
}
void	print_exec(t_list	*exec_lst)
{
	t_exec_node	*current;

	while (exec_lst)
	{
		current = (t_exec_node *)exec_lst->content;
		ft_printf("====EXEC NODE=====\n\n");
		ft_printf("IO:	[%d;%d]\n", (current->io)[0], (current->io)[1]);
		ft_printf("in:	%s\nout:	%s\n",
			(current->filename)[0], (current->filename)[1]);
		print_cmd(current->cmd);
		ft_printf("=================\n\n");
		exec_lst = exec_lst->next;
	}
}
