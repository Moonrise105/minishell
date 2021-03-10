/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:22:13 by moonrise          #+#    #+#             */
/*   Updated: 2021/03/10 16:58:14 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cd_pwd_set(t_list *dict, char *path, char **args)
{
	char	*tmp;
	t_pair	*pwd;
	char	*dir;

	dir = NULL;
	pwd = dict_get(dict, "PWD");
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
	if (dir)
		free(dir);
	if (args[0] && !ft_strcmp(args[0], "-"))
		print_newline(path, 1);
}

int			cd_chdir(char *path, t_list *dict, char **args)
{
	if (chdir(path) < 0)
	{
		chdir_error(path);
		return (1);
	}
	else
		cd_pwd_set(dict, path, args);
	return (0);
}

int			cd_tilda(t_list *dict, char **path)
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

int			cd_minus(t_list *dict, char **path)
{
	t_pair		*old_pwd;

	old_pwd = dict_get(dict, "OLDPWD");
	if (old_pwd && *old_pwd->value)
		*path = ft_strdup(old_pwd->value);
	else
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		if (path && *path)
			free(*path);
		return (1);
	}
	return (0);
}

int			cd(char **args)
{
	t_list		*dict;
	char		*path;
	int			code;

	path = NULL;
	dict = env_get(NULL);
	if (!args[0])
	{
		if (cd_tilda(dict, &path) == 1)
			return (1);
	}
	else if (!ft_strcmp(args[0], "-"))
	{
		if (cd_minus(dict, &path) == 1)
			return (1);
	}
	else
		path = ft_strdup(args[0]);
	code = cd_chdir(path, dict, args);
	free(path);
	return (code);
}
