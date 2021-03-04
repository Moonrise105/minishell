#include "minishell_new.h"

int		cd(char **args)
{
	t_list *dict;
	char **env;
	char *path;
	t_pair *home;
	t_pair *pwd;
	t_pair *old_pwd;
	char *error;
	char *dir;

	dir = NULL;
	dict = env_get(NULL);
	home = dict_get(dict, "HOME");
	pwd = dict_get(dict, "PWD");

	if (!args[0] || !ft_strcmp(args[0], "~"))
	{
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		if (!(home->value) || !(*(home->value)))
			path = "/";
			
		else
			path = home->value;
			
	}
	else if (!ft_strcmp(args[0], "-"))
	{
		old_pwd = dict_get(dict, "OLDPWD");
		if (old_pwd && *old_pwd->value)
			path = old_pwd->value;
			
		else
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
	}
	else
		path = args[0];

	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
		
	else
	{
		if (pwd)
			dict_set(dict, "OLDPWD", pwd->value);
		else
			dict_set(dict, "OLDPWD", "");
			
		dir = getcwd(dir, 100);
		dict_set(dict, "PWD", dir);
		if (args[0] && !ft_strcmp(args[0], "-"))
		{
			ft_putstr_fd(path, 1);
			ft_putstr_fd("\n", 1);
		}
	}
	return (0);
}

int		pwd(char **args)
{
	char dir[500];

	getcwd(dir, 500);
	ft_putstr(dir);
	ft_putstr("\n");
	//free(dir);
	status = 0;
	return (0);
}