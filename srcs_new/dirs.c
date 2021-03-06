/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:22:13 by moonrise          #+#    #+#             */
/*   Updated: 2021/03/06 03:35:37 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

void	chdir_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}


int		cd_chdir(char *path, t_list *dict, char **args)
{
	char	*dir;
	t_pair	*pwd;
	char	*tmp;
	dir = NULL;

	pwd = dict_get(dict, "PWD");
	if (chdir(path) < 0)
	{
		chdir_error(path);
		return (1);
	}
	else
	{
		if (pwd)
		{
			tmp = ft_strdup(pwd->value);
			dict_set(dict, "OLDPWD", tmp);
			free(tmp);
		}
			
		else
			dict_set(dict, "OLDPWD", "");
		dir = getcwd(dir, 100);
		dict_set(dict, "PWD", dir);
		if (args[0] && !ft_strcmp(args[0], "-"))
			print_newline(path, 1);
	}
	if (dir)
		free(dir);
	return (0);
}

int		cd_tilda(t_list *dict, char **args, char **path)
{
	t_pair	*home;

	home = dict_get(dict, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (!(home->value) || !(*(home->value)))
		*path = ft_strdup("/");
		
	else
		*path = ft_strdup(home->value);
	return (0);
}

int		cd(char **args)
{
	t_list *dict;
	char **env;
	char *path;
	t_pair *pwd;
	t_pair *old_pwd;
	int code;

	path = NULL;
	dict = env_get(NULL);
	//home = dict_get(dict, "HOME");
	if (!args[0])
	{
		if (cd_tilda(dict, args, &path) == 1)
			return (1);
			
	}
	else if (!ft_strcmp(args[0], "-"))
	{
		old_pwd = dict_get(dict, "OLDPWD");
		if (old_pwd && *old_pwd->value)
			path = ft_strdup(old_pwd->value);
			
		else
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			if (path)
				free(path);
			return (1);
		}
	}
	else
		path = ft_strdup(args[0]);
	code = cd_chdir(path, dict, args);
	free(path);
	return (code);
}

int		pwd(char **args)
{
	char dir[500];

	getcwd(dir, 500);
	ft_putstr(dir);
	ft_putstr("\n");
	//free(dir);
	g_status = 0;
	return (0);
}