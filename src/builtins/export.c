#include "minishell.h"
#include "error.h"

static int			print_export(t_env_lst *env);
static t_env_lst	*create_exp_node(char *cmd);
static int			find_char(char *cmd, char c);

int	ft_export(char **cmd, t_env_lst *env)
{
	int i;
	
	if (!cmd[1])
		return (print_export(env));
	i = 1;
	while (cmd[i])
	{
		env_add_back(&env, create_exp_node(cmd[i]));
		// ft_putstr_fd("minishell: export: '", 2);
		// ft_putstr_fd(cmd[i], 2);
		// ft_putendl_fd("': not a valid identifier", 2);
		// return (ERR_ARGS);
		i++;
	}
	
	return (SUCCESS);
}

// TODO: print ascii sorted
static int	print_export(t_env_lst *env)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (printf("declare -x %s", tmp->name) == -1)
			return (ERR_PRINT);
		if (tmp->value)
		{
			if (printf("=\"%s\"", tmp->value) == -1)
				return (ERR_PRINT);
		}
		if (printf("\n") == -1)
			return (ERR_PRINT);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static t_env_lst	*create_exp_node(char *cmd)
{
	t_env_lst	*new;
	int			i;

	if (!isalpha(cmd[0]) && cmd[0] != '_')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("\': not a valid identifier", 2);
		return (NULL);
	}
	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (NULL);
	i = find_char(cmd, '=');
	if (i == -1)
		new->name = ft_strdup(cmd);
	else
		new->name = ft_substr(cmd, 0, i);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	if (i > 0)
	{
		new->value = ft_substr(cmd, i + 1, ft_strlen(cmd));
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (NULL);
		}
	}
	else if(i == -1)
		new->value = NULL;
	return (new);
}

 //TODO: 
/** mlouis@z3r11p3:~$ export test=7 =hello hello="yoyoyoyo"
 * bash: export: `=hello': not a valid identifier
 * mlouis@z3r11p3:~$ export | grep hello
 * declare -x hello="yoyoyoyo"
 */

/**
 * $> export *test=test hello=opittr
 * bash: export: `*test=test': not a valid identifier
 * 
 * mlouis@z3r11p3:~$ export | grep hello
 * declare -x hello="opittr"
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
