#include "libft.h"
#include "minishell.h"
#include "builtins.h"
#include "error.h"
#include "exec.h"

char	*find_path(char *cmd, t_env_lst *env)
{
	char	**paths;
	char	*path;
	size_t	i;

	paths = ft_split(get_env_val(env, "PATH", 0), ':');
	if (!paths)
		return (NULL);
	i = 0;
	path = NULL;
	while (paths[i])
	{
		path = ft_concat(3, paths[i], "/", cmd);
		if (!path || !access(path, F_OK & X_OK))
		{
			break ;
		}
		free(path);
		path = NULL;
		i++;
	}
	ft_free_arr(paths);
	return (path);
}

t_bool	is_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
		return (1);
	if (ft_strncmp(cmd[0], "echo", 5))
		if (ft_strncmp(cmd[0], "cd", 3))
			if (ft_strncmp(cmd[0], "pwd", 4))
				if (ft_strncmp(cmd[0], "export", 7))
					if (ft_strncmp(cmd[0], "unset", 6))
						if (ft_strncmp(cmd[0], "exit", 5))
							return (!ft_strncmp(cmd[0], "env", 4));
	return (TRUE);
}

int	call_cmd(char **cmd, t_env_lst *env)
{
	if (!cmd[0])
		return (SUCCESS);
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (ft_echo(cmd, env));
	if (!ft_strncmp(cmd[0], "cd", 3))
		return (ft_cd(cmd, env));
	if (!ft_strncmp(cmd[0], "pwd", 4))
		return (ft_pwd(cmd, env));
	if (!ft_strncmp(cmd[0], "export", 7))
		return (ft_export(cmd, env));
	if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(cmd, env));
	if (!ft_strncmp(cmd[0], "exit", 5))
		return (ft_exit(cmd, env));
	if (!ft_strncmp(cmd[0], "env", 4))
		return (ft_env(cmd, env));
	return (1);
}
