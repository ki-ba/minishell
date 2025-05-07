#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

int	check_quotes(char *line)
{
	size_t	simple_n;
	size_t	double_n;
	size_t	i;

	simple_n = 0;
	double_n = 0;
	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] == '"')
			++double_n;
		else if (line[i] == '\'')
			++simple_n;
		++i;
	}
	return (simple_n % 2 || double_n % 2);
}

size_t	count_token_len(char *line)
{
	size_t	i;
	int		simple_q;
	int		double_q;

	i = 0;
	simple_q = 0;
	double_q = 0;
	while (line[i] && (line[i] != ' ' || simple_q || double_q))
	{
		if (line[i] == '"')
			double_q = !double_q;
		else if (line[i] == '\'')
			simple_q = !simple_q;
		++i;
	}
	return (i);
}

t_bool	determine_redirect(char token_str[])
{
	if (ft_strncmp(token_str, ">", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(token_str, "<", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(token_str, ">>", 3) == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	determine_option(char token_str[])
{
	return (ft_strlen(token_str) == 2 && token_str[0] == '-');
}

t_token_type	determine_token_type(char token_str[], t_token_type last_type)
{
	if (determine_redirect(token_str))
		return (TOKEN_REDIRECT);
	else if (last_type == TOKEN_FILE && ft_str_is_alnum(token_str))
		return (TOKEN_CMD);
	else if (last_type == TOKEN_REDIRECT)
		return (TOKEN_FILE);
	else if (determine_option(token_str))
		return (TOKEN_OPT);
	else if (token_str[0] == '|')
		return (TOKEN_PIPE);
	else
		return (TOKEN_STR);
}

t_token	*create_token(t_list **tokens, char *token_str)
{
	t_token_type	last_type;
	t_list			*last_lst;
	t_token			*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	last_lst = ft_lstlast(*tokens);
	last_type = TOKEN_PIPE;
	if (last_lst)
		last_type = ((t_token *)(last_lst->content))->type;
	if (last_type == TOKEN_PIPE)
		new_token->type = determine_token_type(token_str, last_type);
	new_token->token = token_str;
	return (new_token);
}

void	tokenize(t_list **tokens, char *line)
{
	t_token			*token;
	/*t_token_type	last_type;*/
	size_t			cur_token_len;
	size_t			i;

	i = 0;
	if (!line || check_quotes(line))
		return ;
	while (line[i])
	{
		cur_token_len = count_token_len(&line[i]);
		token = create_token(tokens, ft_substr(line, i, cur_token_len));
		ft_lstadd_back(tokens, ft_lstnew(token));
		ft_printf("new size of list: %d\n", ft_lstsize(*tokens));
		i += cur_token_len;
		while (line[i] == ' ') // FIXME replace by iswhitespace()
			++i;
	}
}

int	interpret_line(char cmd[], t_env_lst *env_lst)
{
	t_list	*tokens;

	tokens = NULL;
	tokenize(&tokens, cmd);
	print_token_list(tokens);
	(void)cmd;
	(void)env_lst;
	return (0);
}

int	readline_loop(t_env_lst *env_lst)
{
	char	*cmd;
	int		status;

	while (TRUE)
	{
		cmd = readline("zinzinshell >");
		add_history(cmd);
		status = interpret_line(cmd, env_lst);
	}
	return (status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env_lst	*env_lst;
	int			exit_status;

	env_lst = NULL;
	(void)argc;
	(void)argv;
	env_lst = create_environment(&env_lst, envp);
	exit_status = readline_loop(env_lst);
	return (exit_status);
}
