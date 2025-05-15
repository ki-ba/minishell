#include "minishell.h"

/**
 * @brief helper function to for check_quotes.
 */
int	check_open(int open, char c)
{
	if (c == '\'')
	{
		if (open == 0)
			open = 1;
		else if (open == 1)
			open = 0;
	}
	if (c == '"')
	{
		if (open == 0)
			open = 2;
		else if (open == 2)
			open = 0;
	}
	return (open);
}

/**
 * @brief checks wether the provided `line` has unclosed quotes.
 * @param open is 0 when not open, 1 when single quote, 2 when double.
 * @returns 0 if all quotes are correctly closed, non-zero otherwise.
 */
int	check_quotes(char *line)
{
	size_t	i;
	int		open;

	open = 0;
	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] == '\'' || line [i] == '"')
			open = check_open(open, line[i]);
		++i;
	}
	return (open);
}

size_t	count_token_len(char *line)
{
	size_t		i;
	int			simple_q;
	int			double_q;

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

t_bool	determine_pipe(char token_str[])
{
	return (!ft_strncmp(token_str, "|", 2));
}
