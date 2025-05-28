/**
*	@brief counts the number of 'parts' in provided string.
*	@brief a part is either an env. variable name, or a string
*	@brief that is between two env. variable names, or between a variable
*	@brief name and the beginning/end of the string.
*	@brief for instance, "Hi $USR you are at $PWD" contains 4 parts.
*/
#include "libft.h"
#include "minishell.h"

static	void	join_in_place(char **s1, char *s2)
{
	char	*s3;

	s3 = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = s3;
}

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

static size_t	get_part_len(char str[])
{
	size_t	part_len;

	if (str[0] == '$')
		part_len = varnamelen(&str[0]);
	else
		part_len = ft_strlen_c(&str[0], '$');
	return (part_len);
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

char	*expand_line(t_env_lst *env, char str[])
{
	size_t	i;
	size_t	part_len;
	char	*env_val;
	char	*expanded;
	char	*part;

	i = 0;
	expanded = ft_calloc(1, sizeof(char));
	env_val = NULL;
	while (str[i])
	{
		part_len = get_part_len(&str[i]);
		part = ft_substr(&str[i], 0, part_len);
		if (part[0] == '$' && must_expand(str, i))
		{
			env_val = get_env_val(env, &part[1]);
			if (env_val)
				join_in_place(&expanded, env_val);
		}
		else
			join_in_place(&expanded, part);
		i += part_len;
		free(part);
	}
	return (expanded);
}
