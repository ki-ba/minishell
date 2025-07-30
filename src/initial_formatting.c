#include "minishell.h"

char	*trim_cmd(char *cmd)
{
	char	*trim;
	size_t	len;

	trim = ft_strtrim(cmd, " \t\n\r\v\f");
	len = ft_strlen(trim);
	free(cmd);
	if (!trim)
		return (NULL);
	if (trim[0] && (trim[0] == '|' || trim[len - 1] == '|'))
	{
		free(trim);
		return (NULL);
	}
	if (trim[0] && (trim[len - 1] == '<' || trim[len - 1] == '>'))
	{
		free(trim);
		return (NULL);
	}
	return (trim);
}

char	*format_cmd(t_env_lst *env, char *cmd)
{
	char	*expanded;

	if (check_meta_validity(cmd))
		return (NULL);
	expanded = expand_line(env, cmd);
	free(cmd);
	expanded = trim_cmd(expanded);
	if (check_parsing(expanded))
		return (NULL);
	return (expanded);
}
