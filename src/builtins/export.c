#include "minishell.h"
#include "error.h"

static int	print_export(t_env_lst *env);
static int	create_exp_node(char *cmd, t_env_lst *env);
static int	update_exp_node(char *cmd, t_env_lst *env);
int	check_name_validity(char *cmd);
static int	find_char(char *cmd, char c);

int	ft_export(char **cmd, t_env_lst *env)
{
	int	i;
	int	err;
	int	c_err;

	err = 0;
	c_err = 0;
	if (!cmd[1])
		return (print_export(env));
	i = 1;
	while (cmd[i])
	{
		err = create_exp_node(cmd[i], env);
		if (err == ERR_ARGS)
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			c_err = 1;
		}
		else if (err == ERR_ALLOC)
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("': allocation failed", 2);
			return (err);
		}
		i++;
	}
	return (c_err);
}

// static t_env_lst	*dup_node(t_env_lst *node)
// {
// 	t_env_lst	*cpy;

// 	cpy = malloc(sizeof(t_env_lst));
// 	cpy->name = ft_strdup(node->name);
// 	cpy->value = ft_strdup(node->value);
// 	cpy->next = NULL;
// 	return (cpy);
// }

static t_env_lst	*dup_env(t_env_lst *env)
{
	t_env_lst	*dup;
	t_env_lst	*tmp;
	t_env_lst	*cpy;

	if (!env)
		return (NULL);
	tmp = env;
	dup = NULL;
	while (tmp)
	{
		cpy = malloc(sizeof(t_env_lst));
		cpy->name = ft_strdup(tmp->name);
		cpy->value = ft_strdup(tmp->value);
		cpy->next = NULL;
		env_add_back(&dup, cpy);
		// env_add_back(&dup, dup_node(tmp));
		tmp = tmp->next;
	}
	return (dup);
}

static void	swap_nodes(t_env_lst **head, t_env_lst *prev, t_env_lst *n1, t_env_lst *n2)
{
	if (!n1 || !n2)
		return ;
	n1->next = n2->next;
	n2->next = n1;
	if (prev)
		prev->next = n2;
	else
		*head = n2;
}

t_env_lst	*sort_env_var(t_env_lst *env)
{
	int			is_sorted;
	t_env_lst	*prev;
	t_env_lst	*tmp;

	if (!env)
		return (NULL);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		tmp = env;
		prev = NULL;
		while (tmp && tmp->next)
		{
			if (ft_strncmp(tmp->name, tmp->next->name, ft_strlen(tmp->name) + 1) > 0)
			{
				swap_nodes(&env, prev, tmp, tmp->next);
				is_sorted = 0;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (env);
}

// TODO: print ascii sorted
static int	print_export(t_env_lst *env)
{
	t_env_lst	*tmp;

	tmp = dup_env(env);
	if (!tmp)
		return (ERR_ALLOC);
	tmp = sort_env_var(tmp);
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
	destroy_env_lst(tmp);
	return (SUCCESS);
}


//TODO: check name doesn't alreayd exist
// if name exist and val null => replace that val with new val
// if name exist and val too => check new val not null and if so replace
static int	create_exp_node(char *cmd, t_env_lst *env)
{
	int			i;
	t_env_lst 	*new;

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
	if (search_env_var(env, new->name) != NULL)
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
	else if(i == -1)
		new->value = NULL;
	env_add_back(&env, new);
	return (SUCCESS);
}

static int	update_exp_node(char *cmd, t_env_lst *env)
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
		node = search_env_var(env, name);
		node->value = ft_substr(cmd, i + 1, ft_strlen(cmd));
		if (!node->value)
			return (ERR_ALLOC);
	}
	return (SUCCESS);
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

int	check_name_validity(char *cmd)
{
	int	i;

	if (!isalpha(cmd[0]) && cmd[0] != '_')
		return (ERR_ARGS);
	i = 1;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!isalnum(cmd[i]) && cmd[i] != '_')
			return (ERR_ARGS);
		i++;
	}
	return (SUCCESS);
}

//TODO: libft??
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
