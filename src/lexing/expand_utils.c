#include "minishell.h"

void	join_in_place(char **s1, char *s2)
{
	char	*s3;

	s3 = ft_strjoin(*s1, s2);
	free(s2);
	free(*s1);
	*s1 = s3;
}

size_t	varnamelen(char str[])
{
	size_t	i;

	if (str[0] != '$')
		return (0);
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		++i;
	if (str[i] == '?' && !str[i + 1])
		++i;
	return (i);
}

// TODO: space before after spe-K
size_t	get_part_len(char str[])
{
	size_t	i;
	size_t	tmp;

	i = 0;
	if (str[0] == '$')
		i = varnamelen(str);
	else
		i = ft_strlen_c(str, '$');
	tmp = ft_strlen_c(str, '|');
	if (i > tmp && tmp > 0)
		i = tmp;
	printf("|+ tmp [%zu] ; i [%zu]\n", tmp, i);
	tmp = ft_strlen_c(str, '<');
	if (i > tmp && tmp > 0)
		i = tmp;
	printf("<+ tmp [%zu] ; i [%zu]\n", tmp, i);
	tmp = ft_strlen_c(str, '>');
	if (i > tmp && tmp > 0)
		i = tmp;
	printf(">+ tmp [%zu] ; i [%zu]\n", tmp, i);
	return (i);
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

// char	*expand_meta_char(char *str, size_t i, size_t len)
// {

// }

// TODO: space before after spe-K
char	*set_chunk_val(t_env_lst *env, char *str, size_t i, size_t len)
{
	char	*next_chunk;
	char	*varname;
	char	*meta;

	printf("++len= %zu ; i= %zu ; str[i]= %c\n", len, i, str[i]);

	if (str[i] == '$' && must_expand(str, i) &&
		(len > 1 || (str[i + 1] == '?' && len == 1)))
	{
		if (len > 1)
			varname = ft_substr(str, i + 1, len - 1);
		else
			varname = ft_substr(str, i + 1, len);
		next_chunk = ft_strdup(get_env_val(env, varname, 0));
		printf("helo= %s\n", next_chunk);
		free(varname);
	}
	else if (i > 0 && must_expand(str, i - 1) &&
		(str[i - 1] == '|' || str[i - 1] == '<' || str[i - 1] == '>'))
	{
		// // next_chunk = expand_meta_char(str, i, len);
		// printf("STR= '%s'\n", str);
		// if (str[i - 1] != '|' && str[i] == str[i + 1])
		// 	varname = ft_substr(str, i, 2);
		// else
		// 	varname = ft_substr(str, i, 1);
		// printf("vn= '%s'\n", varname);
		// len = get_part_len(&str[i]);
		// printf("len= %zu ; i= %zu\n", len, i);
		// if (len < i)
		// 	len = ft_strlen(&str[i]);
		// next_chunk = ft_concat(4, " ", varname, " ", ft_substr(str, i + 1, i));
		
		--i;
		// 	// next_chunk = ft_concat(2, " ", &str[i - 1]);
		varname = ft_substr(str, i + 1, len);
		printf("varn= '%s'\n", varname);
		meta = ft_calloc(3, sizeof (char));
		meta[0] = str[i];
		printf("meta= %c ; +1= %c\n", str[i], str[i - 1]);
		if (str[i] != '|' && str[i] == str[i - 1])
			meta[1] = meta[0];
		next_chunk = ft_concat(4, " ", meta, " ", varname);
		printf("chunkyyyyyyyyy= %s\n", next_chunk);
		free(varname);
	}
	else //if (i == 0)
	{
		next_chunk = ft_substr(str, i, len);
		printf("qwe= %s\n", next_chunk);
		if (!next_chunk)
			return (NULL);
	}
	// else
	// {
	// 	next_chunk = ft_substr(str, i + 1, len);
	// 	printf("zzlo= %s\n", next_chunk);
	// 	if (!next_chunk)
	// 		return (NULL);
	// }
	return (next_chunk);
}

