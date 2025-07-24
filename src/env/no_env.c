#include "minishell.h"
#include <unistd.h>

static void	add_pwd(t_env_lst **env_lst);
static void	add_oldpwd(t_env_lst **env_lst);

t_env_lst	**empty_env_check(t_env_lst **env_lst)
{
	t_env_lst	*check;

	check = search_env_var(*env_lst, "?PWD");
	if (!check)
		add_pwd(env_lst);
	check = search_env_var(*env_lst, "?OLDPWD");
	if (!check)
		add_oldpwd(env_lst);
	check = search_env_var(*env_lst, "SHLVL");
	if (!check)
		env_add_back(env_lst, new_env_entry("SHLVL", "1"));
	return (env_lst);
}

static void	add_pwd(t_env_lst **env_lst)
{
	t_env_lst	*check;
	char		*name;

	name = NULL;
	name = getcwd(name, PATH_MAX);
	env_add_back(env_lst, new_env_entry("?PWD", name));
	check = search_env_var(*env_lst, "PWD");
	if (!check)
		env_add_back(env_lst, new_env_entry("PWD", name));
	free(name);
}

static void	add_oldpwd(t_env_lst **env_lst)
{
	t_env_lst	*check;

	env_add_back(env_lst, new_env_entry("?OLDPWD", NULL));
	check = search_env_var(*env_lst, "OLDPWD");
	if (!check)
		env_add_back(env_lst, new_env_entry("OLDPWD", NULL));
}
