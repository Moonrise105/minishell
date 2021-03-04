#include "minishell.h"

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
	//dir = malloc(sizeof(char) * 100);
	dir = NULL;
	//ft_putstr("MYCD\n");
	env = env_get(NULL);
	dict = dict_create(env, '=');
	home = dict_get(dict, "HOME");
	pwd = dict_get(dict, "PWD");

	if (!args[0] || !ft_strcmp(args[0], "~"))
	{
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			//dict_free(&dict);
			return (1);
		}
		if (!(home->value) || !(*(home->value)))
		{
			//ft_putstr("IN1\n");
			path = "/";
		}
			
		else
		{
			//ft_putstr("IN2\n");
			path = home->value;
		}
			
	}
	else if (!ft_strcmp(args[0], "-"))
	{
		old_pwd = dict_get(dict, "OLDPWD");
		if (old_pwd && *old_pwd->value)
		{
			path = old_pwd->value;
		}
			
		else
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			//dict_free(&dict);
			return (1);
		}
			
	}
	else
		path = args[0];

	if (chdir(path) < 0)
	{
		//error = ft_strjoin("minishell: cd: ")
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		//dict_free(&dict);
		return (1);
	}
		
	else
	{
		//printf("%s\n", path);
		if (pwd)
			dict_set(dict, ft_strdup("OLDPWD"), pwd->value);
		else
		{
			dict_set(dict, ft_strdup("OLDPWD"), ft_strdup(""));
		}
			
		dir = getcwd(dir, 100);
		dict_set(dict, ft_strdup("PWD"), dir);
		if (args[0] && !ft_strcmp(args[0], "-"))
		{
			ft_putstr_fd(path, 1);
			ft_putstr_fd("\n", 1);
		}
		env_get(dict_to_arr(dict));
	}
	//dict_free(&dict);
	return (0);
}

int		pwd(char **args)
{
	char dir[100];

	getcwd(dir, 100);
	ft_putstr(dir);
	ft_putstr("\n");
	//free(dir);
	status = 0;
	return (0);
}

int		is_numeric(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (0);
		++i;
	}
	return (1);
}

int		my_exit(char **args, t_parser *p)
{
	int i;
	int code;
	char *c;

	i = 0;

	if (args)
	{
		while (args[i]) 
		{
			if (i > 0)
			{
				ft_putstr("exit\n");
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				return (127);
			}

			if (!is_numeric(args[i]))
			{
				ft_putstr("exit\n");
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				commands_free(&(p->commands));
				parser_free(p);
				//free_array_char(args - 1);
				free(args - 1);
				env_get(&c);
				exit(255);
			}
			
			++i;
		}
		ft_putstr("exit\n");
		code = (args[0]) ? ft_atoi_orig(args[0]) : 0;
		commands_free(&(p->commands));
		parser_free(p);
		//free_array_char(args - 1);
		free(args - 1);
		env_get(&c);
		exit(code);

	}
	commands_free(&(p->commands));
	parser_free(p);
	env_get(&c);
	//free_array_char(args);
	//free(args);
	ft_putstr("exit\n");
	exit(0);
	return (0);
}