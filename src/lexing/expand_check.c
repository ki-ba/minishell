#include "minishell.h"

int	is_metachar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

t_bool	is_inquote(char *str, size_t pos)
{
	size_t	i;
	int		sq;
	int		dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (i < pos)
	{
		if (str[i] == '\'')
			++sq;
		if (str[i] == '"')
			++dq;
		++i;
	}
	return ((sq % 2) + (dq % 2) % 2);
}

t_bool	must_expand(char str[], size_t pos)
{
	char	quote;
	size_t	i;

	i = 0;
	quote = '\0';
	while (i < pos)
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = '\0';
		++i;
	}
	return (quote != '\'');
}

int	check_meta_validity(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (is_metachar(str[i]) && !is_inquote(str, i))
		{
			if (str[i] == '|' && ((str[i + 1] == '>' || str[i + 1] == '<')))
				return (ERR_PARSING);
			if (str[i] == '>' && ((str[i + 1] == '|' || str[i + 1] == '<')))
				return (ERR_PARSING);
			if (str[i] == '<' && ((str[i + 1] == '|' || str[i + 1] == '>')))
				return (ERR_PARSING);
			if (str[i] == '<' || str[i] == '>')
			{
				if (str[i + 1] == str[i] && str[i + 2] == str[i])
					return (ERR_PARSING);
			}
		}
		++i;
	}
	return (SUCCESS);
}
