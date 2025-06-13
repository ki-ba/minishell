#include "minishell.h"
#include "builtins.h"
#include "error.h"

static int	print_export(t_env_lst *env);
static int	create_exp_node(char *cmd, t_env_lst **env);
static int	update_exp_node(char *cmd, t_env_lst **env);

int	ft_export(char **cmd, t_env_lst *env)
{
	int	i;
	int	err;
	int	c_err;

	err = 0;
	c_err = 0;
	printf("exp= %p\n", &env);
	if (!cmd[1])
		return (print_export(env));
	i = 1;
	while (cmd[i])
	{
		err = create_exp_node(cmd[i], &env);
		if (err == ERR_ARGS)
		{
			ft_printf_fd(2,
				"minishell: export: '%s': not a valid identifier\n", cmd[i]);
			c_err = 1;
		}
		else if (err == ERR_ALLOC)
			return (err);
		i++;
	}
	return (c_err);
}

static int	print_export(t_env_lst *env)
{
	t_env_lst	*tmp;

	tmp = dup_env(env);
	if (!tmp)
		return (ERR_ALLOC);
	tmp = sort_env_var(tmp);
	while (tmp)
	{
		if (check_name_validity(tmp->name) == SUCCESS)
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
		}
		tmp = tmp->next;
	}
	destroy_env_lst(tmp);
	return (SUCCESS);
}

//TODO: check name doesn't alreayd exist
// if name exist and val null => replace that val with new val
// if name exist and val too => check new val not null and if so replace
static int	create_exp_node(char *cmd, t_env_lst **env)
{
	int			i;
	t_env_lst	*new;

	if (check_name_validity(cmd) == ERR_ARGS)
		return (ERR_ARGS);
	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (ERR_ALLOC);
	i = find_char(cmd, '=');
	if (i == -1)
		new->name = ft_strdup(cmd);
	else
		new->name = ft_substr(cmd, 0, i);
	if (!new->name)
	{
		free(new);
		return (ERR_ALLOC);
	}
	if (search_env_var(*env, new->name) != NULL)
	{
		free(new->name);
		free(new);
		return (update_exp_node(cmd, env));
	}
	if (i >= 0)
	{
		new->value = ft_substr(cmd, i + 1, ft_strlen(cmd));
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (ERR_ALLOC);
		}
	}
	else if (i == -1)
		new->value = NULL;
	new->next = NULL;
	env_add_back(env, new);
	return (SUCCESS);
}

static int	update_exp_node(char *cmd, t_env_lst **env)
{
	int			i;
	char		*name;
	t_env_lst	*node;

	i = find_char(cmd, '=');
	if (i == -1)
		name = ft_strdup(cmd);
	else
		name = ft_substr(cmd, 0, i);
	if (!name)
		return (ERR_ALLOC);
	if (i > 0)
	{
		node = search_env_var(*env, name);
		node->value = ft_substr(cmd, i + 1, ft_strlen(cmd));
		if (!node->value)
			return (ERR_ALLOC);
	}
	return (SUCCESS);
}

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
