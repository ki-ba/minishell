#include "minishell.h"

// static t_bool	ft_isquote(char c)
// {
// 	return (c == '\'' || c == '"');
// }

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
		if (str[i] == '<' || str[i] == '>')
			++i;
		if (str[i] == '<' || str[i] == '>')
			++i;
		part_len = get_part_len(&str[i]);
		next_chunk = set_chunk_val(env, str, i, part_len);
		i += part_len;
		if ((str[i] == '?' && i > 0 && str[i - 1] == '$') || str[i] == '|' | str[i] == '<' || str[i] == '>')
			++i;
		if (str[i] == '<' || str[i] == '>')
			++i;
		join_in_place(&expanded, next_chunk);
		if (!expanded)
			return (NULL);
	}
	if (DEBUG)
		printf("EXPANDED= %s\n", expanded);
	return (expanded);
}

/**
*	@brief counts the number of 'parts' in provided string.
*	@brief a part is either an env. variable name, or a string
*	@brief that is between two env. variable names, or between a variable
*	@brief name and the beginning/end of the string.
*	@brief for instance, "Hi $USR you are at $PWD" contains 4 parts.
*/
// size_t	count_parts(char *line)
// {
// 	size_t	i;
// 	size_t	n;
// 	size_t	len;
//
// 	last_del = '\0';
// 	i = 0;
// 	n = 0;
// 	quote = 0;
// 	len = ft_strlen(line);
// 	quote = '\0';
// 	while (i < len)
// 	{
// 		++n;
// 		i += get_part_len(&line[i]);
// 	}
// 	return (n);
// }

// char	**split_vars(char *line)
// {
// 	char	**arr;
// 	size_t	nb_parts;
// 	size_t	i;
// 	size_t	j;
//
// 	i = 0;
// 	j = 0;
// 	nb_parts = count_parts(line);
// 	arr = ft_calloc(nb_parts, sizeof(char *));
// 	if (!arr)
// 		return (NULL);
// 	while (i < nb_parts)
// 	{
// 		arr[i] = ft_substr(line, j, get_part_len(&line[j]));
// 		if (!arr[i])
// 		{
// 			ft_free_arr(arr);
// 			return (NULL);
// 		}
// 	}
// 	arr[i] = (NULL);
// 	return (arr);
// }

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
				continue;
			}
			if (str[i] == '|' && ((str[i + 1] == '>' || str[i + 1] == '<')) )
								// || (i > 0 && (str[i - 1] == '>' || str[i - 1] == '<'))))
				return (ERR_PARSING);
			if (str[i] == '>' && ((str[i + 1] == '|'|| str[i + 1] == '<')) )
								// || (i > 0 && (str[i - 1] == '|' || str[i - 1] == '<'))))
				return (ERR_PARSING);
			if (str[i] == '<' && ((str[i + 1] == '|'|| str[i + 1] == '>')) )
								// || (i > 0 && (str[i - 1] == '|' || str[i - 1] == '>'))))
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
