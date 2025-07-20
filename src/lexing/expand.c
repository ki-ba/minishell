#include "minishell.h"

// TODO: space before after spe-K
char	*expand_line(t_env_lst *env, char str[])
{
	size_t	i;
	size_t	part_len;
	char	*expanded;
	char	*next_chunk;

	i = 0;
	expanded = ft_calloc(1, sizeof(char));
	if (!expanded)
		return (NULL);
	while (str[i])
	{
		// if (str[i] == '<' || str[i] == '>')
		// 	++i;
		// if (str[i] == '<' || str[i] == '>')
		// 	++i;
		part_len = get_part_len(&str[i]);
		next_chunk = set_chunk_val(env, str, i, part_len);
		i += part_len;
		if (!is_inquote(str, i) && (str[i] == '|' || str[i] == '<' || str[i] == '>'))
			++i;
		if (!is_inquote(str, i) && (str[i] == '<' || str[i] == '>'))
			++i;
		join_in_place(&expanded, next_chunk);
		if (!expanded)
			return (NULL);
	}
	return (expanded);
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

int	check_meta_validity(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && !is_inquote(str, i))
		{
			if (str[i] != '|' && str[i] != '>' && str[i] != '<')
			{
				++i;
				continue ;
			}
			if (str[i] == '|' && ((str[i + 1] == '>' || str[i + 1] == '<')))
				return (ERR_PARSING);
			if (str[i] == '>' && ((str[i + 1] == '|'|| str[i + 1] == '<')))
				return (ERR_PARSING);
			if (str[i] == '<' && ((str[i + 1] == '|'|| str[i + 1] == '>')))
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
