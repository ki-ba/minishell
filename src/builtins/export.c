#include "minishell.h"
#include "error.h"

static int	print_export(t_env_lst *env);
static int	create_exp_node(char *cmd, t_env_lst *env);
static int	update_exp_node(char *cmd, t_env_lst *env);
static int	check_name_validity(char *cmd);
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

// static t_env_lst	*dup_env(t_env_lst *env)
// {
// 	t_env_lst	*tmp;
// 	size_t		*order;
// 	size_t		i;
// 	size_t		j;

// 	tmp = env;
// 	order = ft_calloc(get_env_size(env), sizeof(size_t));
// 	if (!order)
// 		return (NULL);
// 	i = 0;
// 	while (tmp)
// 	{
// 		j = 0;
// 		while (tmp->name[j])
// 		{
// 			order[i] += tmp->name[j];
// 			j++;
// 		}
// 		i++;
// 		tmp = tmp->next;	
// 	}
// 	return (order);
// }

void	swap_adjacent(t_env_lst **head, t_env_lst *prev, t_env_lst *n1, t_env_lst *n2)
{
	n1->next = n2->next;
	n2->next = n1;

	if (prev)
		prev->next = n2;
	else
		*head = n2;
}

t_env_lst	*sort_env_var(t_env_lst *env)
{
	int			sorted;
	t_env_lst	*prev;
	t_env_lst	*curr;
	t_env_lst	*head = env;

	if (!env)
		return (NULL);

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		prev = NULL;
		curr = head;

		while (curr && curr->next)
		{
			if (ft_strncmp(curr->name, curr->next->name, ft_strlen(curr->name)) > 0)
			{
				swap_adjacent(&head, prev, curr, curr->next);
				sorted = 0;
				if (prev == NULL)
					curr = head;
				else
					curr = prev->next;
			}
			prev = curr;
			curr = curr->next;
		}
	}
	return (head);
}

// static void	swap_nodes(t_env_lst *n1, t_env_lst *n2, t_env_lst *prev)
// {
// 	t_env_lst	*swp;

// 	printf("11/ n1= %s ; nn1= %s ; n2= %s ; nn2= %s ; prev= %s ; pn= %s\n", n1->name, n1->next->name, n2->name, n2->next->name, prev->name, prev->next->name);
// 	swp = n2->next;
// 	n2->next = n1;
// 	n1->next = swp;
// 	prev->next = n2;
// 	printf("22/ n1= %s ; nn1= %s ; n2= %s ; nn2= %s ; prev= %s ; pn= %s\n", n1->name, n1->next->name, n2->name, n2->next->name, prev->name, prev->next->name);
// }

// t_env_lst	*sort_env_var(t_env_lst *env)
// {
// 	t_env_lst	*tmp1;
// 	t_env_lst	*tmp2;
// 	t_env_lst	*save;
// 	t_env_lst	*head;
// 	int			is_sorted;

// 	if (!env)
// 		return (NULL);
// 	is_sorted = 0;
// 	tmp1 = env;
// 	head = env;
// 	while (!is_sorted)
// 	{
// 		is_sorted = 1;
// 		while (tmp1)
// 		{
// 			tmp2 = tmp1->next;
// 			save = tmp1;
// 			while (tmp2)
// 			{
// 				if (ft_strncmp(tmp1->name, tmp2->name, ft_strlen(tmp1->name) + 1) > 0)
// 				{
// 					swap_nodes(tmp1, tmp2, save);
// 					is_sorted = 0;
// 					break ;
// 				}
// 				// printf("t1= %s ; t2= %s ; sa= %s\n", tmp1->name, tmp2->name, save->name);
// 				save = save->next;
// 				tmp2 = tmp2->next;
// 			}
// 			tmp1 = tmp1->next;
// 		}
// 	}
// 	return (env);
// }


// static void	swap_nodes(t_env_lst *n1, t_env_lst *n2)
// {
// 	t_env_lst	*swp;

// 	swp = n2;
// 	n1->next = swp->next;
// 	swp->next = n1->next;
// }

// static t_env_lst	*sort_env_var(t_env_lst *env)
// {
// 	t_env_lst	*tmp_i;
// 	t_env_lst	*tmp_j;
// 	t_env_lst	*swp;
// 	t_env_lst	*head;

// 	head = env;
// 	tmp_i = env;
// 	while (tmp_i)
// 	{
// 		tmp_j = tmp_i->next;
// 		while (tmp_j)
// 		{
// 			printf("1/ %s\t%s\n", tmp_i->name, tmp_j->name);
// 			if (ft_strncmp(tmp_i->name, tmp_j->name, ft_strlen(tmp_i->name)) > 0)
// 			{
				
// 			}
// 			printf("2/ %s\t%s\n", tmp_i->name, tmp_j->name);
// 			tmp_j = tmp_j->next;
// 		}
// 		tmp_i = tmp_i->next;
// 	}
// 	return (head);
// }

// TODO: print ascii sorted
static int	print_export(t_env_lst *env)
{
	t_env_lst	*tmp;

	sort_env_var(env);
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

static int	check_name_validity(char *cmd)
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
