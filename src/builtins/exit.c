/**
*	The exit utility shall cause the shell to exit from its current execution
*	environment with the exit status specified by the unsigned decimal
*	integer n.  If the current execution environment is a subshell 
*	environment, the shell shall exit from the subshell environment
*	with the specified exit status and continue in the environment
*	from which that subshell environment was invoked; otherwise, the shell
*	utility shall terminate with the specified exit status. If n is specified,
*	but its value is not between 0 and 255 inclusively, the exit status
*	is undefined. A trap on EXIT shall be executed before the shell
*	terminates, except when the exit utility is invoked in that trap 
*	itself, in which case the shell shall exit immediately.
*/

#include "minishell.h"

int	ft_exit(char **cmd, t_env_lst *env)
{
	(void)cmd;
	(void)env;
	return (ft_printf("TODO : built-in exit\n"));
}
