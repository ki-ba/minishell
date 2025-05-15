/**
*	@brief counts the number of 'parts' in provided string.
*	@brief a part is either an env. variable name, or a string
*	@brief that is between two env. variable names, or between a variable
*	@brief name and the beginning/end of the string.
*	@brief for instance, "Hi $USR you are at $PWD" contains 4 parts.
*/
#include "libft.h"
#include "minishell.h"

static size_t	varnamelen(char str[])
{
	size_t	i;

	if (str[0] != '$')
		return (0);
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		++i;
	return (i);
}

size_t	count_parts(char str[])
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '$')
		{
			++count;
			i += varnamelen(&str[i]);
		}
		else
		{
			++count;
			i += ft_strlen_c(&str[i], '$');
		}
	}
	return (count);
}

char	**split_by_vars(char str[])
{
	size_t	i;
	size_t	part_n;
	char	**arr;
	size_t	size;
	size_t	part_len;

	part_n = 0;
	size = count_parts(str);
	arr = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (part_n < size)
	{
		if (str[i] == '$')
		{
			part_len = varnamelen(&str[i]);
		}
		else
		{
			part_len = ft_strlen_c(&str[i], '$');
		}
		arr[part_n] = ft_substr(str, i, part_len);
		i += part_len;
		++part_n;
	}
	return (arr);
}
