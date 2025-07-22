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
/**
 * exit -25 => $? = 231
 * exit 256 => $? = 0
 * exit 23d => perror letter
 * 
 * exit => last $?
 */

#include <stdint.h>
#include "minishell.h"

static int	check_exit_arg(char **cmd);

int	ft_exit(char **cmd, t_env_lst *env)
{
	unsigned int	ret;

	if (!cmd[1])
		ret = ft_atoi(get_env_val(env,  "?", 0));
	else
	{
		ret = check_exit_arg(cmd);
		if (ret != SUCCESS)
			return (ret);
		ret = ft_atoi(cmd[1]) % 256;
	}
	return (ret);
}

static int	check_exit_arg(char **cmd)
{
	size_t	i;

	if (cmd[2])
	{
		printf("exit\n");
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		return (ERR_ARGS);
	}
	i = 0;
	if (cmd[1][i] == '-' || cmd[1][i] == '+')
		i++;
	while (cmd[1][i] && ft_isdigit(cmd[1][i]))
		i++;
	if (cmd[1][i] != '\0')
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", cmd[1]);
		return (ERR_PARSING);
	}
	return (SUCCESS);
}
