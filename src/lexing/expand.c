/**
*	@brief counts the number of 'parts' in provided string.
*	@brief a part is either an env. variable name, or a string
*	@brief that is between two env. variable names, or between a variable
*	@brief name and the beginning/end of the string.
*	@brief for instance, "Hi $USR you are at $PWD" contains 4 parts.
*/
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

/*size_t	count_parts(char str[])*/
/*{*/
/*	size_t	i;*/
/*	size_t	count;*/
/**/
/*	i = 0;*/
/*	count = 0;*/
/*	while (str[i])*/
/*	{*/
/*		if (str[i] && str[i] == '$')*/
/*		{*/
/*			++count;*/
/*			i += varnamelen(&str[i]);*/
/*		}*/
/*		else*/
/*		{*/
/*			++count;*/
/*			i += ft_strlen_c(&str[i], '$');*/
/*		}*/
/*	}*/
/*	return (count);*/
/*}*/

/*char	**split_by_vars(char str[])*/
/*{*/
/*	size_t	i;*/
/*	size_t	part_n;*/
/*	char	**arr;*/
/*	size_t	size;*/
/*	size_t	part_len;*/
/**/
/*	part_n = 0;*/
/*	size = count_parts(str);*/
/*	arr = ft_calloc(size + 1, sizeof(char *));*/
/*	i = 0;*/
/*	while (part_n < size)*/
/*	{*/
/*		if (str[i] == '$')*/
/*		{*/
/*			part_len = varnamelen(&str[i]);*/
/*		}*/
/*		else*/
/*		{*/
/*			part_len = ft_strlen_c(&str[i], '$');*/
/*		}*/
/*		arr[part_n] = ft_substr(str, i, part_len);*/
/*		i += part_len;*/
/*		++part_n;*/
/*	}*/
/*	return (arr);*/
/*}*/

static size_t	get_part_len(char str[])
{
	size_t	part_len;

	if (str[0] == '$')
		part_len = varnamelen(&str[0]);
	else
		part_len = ft_strlen_c(&str[0], '$');
	return (part_len);
}

/*static char	*extract_part(char str[])*/
/*{*/
/*	size_t	part_len;*/
/**/
/*	if (!str)*/
/*		return (NULL);*/
/*	if (str[0] == '$')*/
/*	{*/
/*		part_len = varnamelen(str);*/
/*	}*/
/*	else*/
/*		part_len = ft_strlen_c(str, '$');*/
/*	return (ft_substr(str, 0, part_len));*/
/*}*/

char	*expand_line(t_env_lst *env, char str[])
{
	size_t	i;
	size_t	part_len;
	char	*env_val;
	char	*expanded;
	char	*part;

	i = 0;
	expanded = ft_calloc(1, sizeof(char));
	while (str[i])
	{
		part_len = get_part_len(&str[i]);
		part = ft_substr(&str[i], 0, part_len);
		if (part[0] == '$')
		{
			env_val = get_env_val(env, &part[1]);
			if (env_val)
				expanded = ft_strjoin(expanded, env_val);
		}
		else
			expanded = ft_strjoin(expanded, part);
		i += part_len;
		free(part);
	}
	return (expanded);
}
