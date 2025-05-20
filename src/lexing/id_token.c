#include "minishell.h"

/**
	* @brief determines if the given string is a redirection meta-character.
*/
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

/**
	* @brief determines if the given string is an option meta-character.
*/
t_bool	determine_option(char token_str[])
{
	return (ft_strlen(token_str) == 2 && token_str[0] == '-');
}

/**
	* @brief determines if the given string is a pipe meta-character.
*/
t_bool	determine_pipe(char token_str[])
{
	return (!ft_strncmp(token_str, "|", 2));
}
