#include "minishell.h"
#include "builtins.h"
#include "error.h"
#include "exec.h"

int	call_cmd(t_exec_node *exe, t_env_lst *env)
{
	if (!exe->cmd[0])
		return (SUCCESS);
	// if (ft_strncmp(cmd[0], "echo", 5))
	// 	return (ft_echo(exe->cmd, env));
	if (ft_strncmp(exe->cmd[0], "cd", 3))
		return (ft_cd(exe->cmd, env));
	if (ft_strncmp(exe->cmd[0], "pwd", 4))
		return (ft_pwd(exe->cmd));
	// if (ft_strncmp(exe->cmd[0], "export", 7))
	// 	return (ft_export(exe->cmd, env));
	// if (ft_strncmp(exe->cmd[0], "unset", 6))
	// 	return (ft_unset(exe->cmd, env));
	// if (ft_strncmp(exe->cmd[0], "exit", 5))
	// 	return (ft_exit(exe->cmd, env));
	// if (ft_strncmp(exe->cmd[0], "env", 4))
	// 	return (ft_env(exe->cmd, env));
	return (simple_cmd(exe, env));
}
