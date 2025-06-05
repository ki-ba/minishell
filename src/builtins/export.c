#include "minishell.h"
#include "error.h"

static int	print_export(t_env_lst *env);
static void	create_exp_node(char *cmd);
static int	find_char(char *cmd, char c);

int	ft_export(char **cmd, t_env_lst *env)
{
	int 		i;
	
	if (!cmd[1])
		return (print_export(env));
	i = 1;
	while (cmd[i])
	{
		create_exp_node(cmd[i]);
		// env_add_back(&env, new)
		// ft_putstr_fd("minishell: export: '", 2);
		// ft_putstr_fd(cmd[i], 2);
		// ft_putendl_fd("': not a valid identifier", 2);
		return (ERR_ARGS);
	}
	
	return (SUCCESS);
}

static int	print_export(t_env_lst *env)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value) == -1)
			return (ERR_PRINT);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static void	create_exp_node(char *cmd)
{
	int	i;

	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (NULL);
	i = find_char(cmd, '=');
	if (!i)
	{
		ft_putstr_fd("minishell: export: \`", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("\': not a valid identifier", 2)
	}
	// if "=" then malloc value and set to null
	// else value = null
	// new->name = malloc();
	// new->value = getenv(name);
	// new->next = NULL;
	// return (new);
}
 //TODO: 
/** mlouis@z3r11p3:~$ export test=7 =hello hello="yoyoyoyo"
 * bash: export: `=hello': not a valid identifier
 * mlouis@z3r11p3:~$ export | grep hello
 * declare -x hello="yoyoyoyo"
 */

/**
 * mlouis@z3r11p3:~$ export tes.t=test
 * bash: export: `tes.t=test': not a valid identifier
mlouis@z3r11p3:~$ export tes/t=test
bash: export: `tes/t=test': not a valid identifier
mlouis@z3r11p3:~$ export 9test=test
bash: export: `9test=test': not a valid identifier
mlouis@z3r11p3:~$ export t9test=test
 */

/**
 * export tes=t=test
 * mlouis@z3r11p3:~$ export
 * declare -x tes="t=test"
 */

static int	find_char(char *cmd, char c)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
