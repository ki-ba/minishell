#include "minishell.h"

int	is_metachar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}
