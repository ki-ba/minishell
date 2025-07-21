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
		++i;
	}
	return (c_err);
}

static int	print_export(t_env_lst *env)
{
	t_env_lst	*tmp;
	t_env_lst	*head;

	tmp = dup_env(env); //TODO: test leak if null
	if (!tmp)
		return (ERR_ALLOC);
	sort_env_var(tmp);
	head = tmp;
	while (tmp)
	{
		if (check_name_validity(tmp->name) == SUCCESS)
		{
			printf("%s", tmp->name);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
	destroy_env_lst(head);
	return (SUCCESS);
}

static int	init_exp_node(char *cmd, t_env_lst *new)
{
	int	i;

	i = find_char(cmd, '=');
	if (i == -1)
	{
		new->name = ft_strdup(cmd);
		new->value = NULL;
	}
	else
	{
		new->name = ft_substr(cmd, 0, i);
		new->value = ft_substr(cmd, i + 1, ft_strlen(cmd));
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (ERR_ALLOC);
		}
	}
	if (!new->name)
	{
		if (new->value)
			free(new->value);
		free(new);
		return (ERR_ALLOC);
	}		
	return (SUCCESS);
}

static int	create_exp_node(char *cmd, t_env_lst **env)
{
	t_env_lst	*new;

	if (check_name_validity(cmd) == ERR_ARGS)
		return (ERR_ARGS);
	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (ERR_ALLOC);
	init_exp_node(cmd, new);
	if (search_env_var(*env, new->name) != NULL)
	{
		free(new->name);
		free(new->value);
		free(new);
		return (update_exp_node(cmd, env));
	}
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
		free(name);
		name = NULL;
		free(node->value);
		node->value = ft_substr(cmd, i + 1, ft_strlen(cmd));
		if (!node->value)
			return (ERR_ALLOC);
	}
	if (name)
		free(name);
	return (SUCCESS);
}
