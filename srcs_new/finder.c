/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:07:42 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 16:29:53 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_file(DIR *dir, char *file)
{
	struct dirent	*f;

	if (dir && file)
	{
		while ((f = readdir(dir)))
		{
			if (ft_strcmp(f->d_name, file) == 0)
				return (1);
		}
	}
	return (0);
}

char	*parse_dirs(char **dirs, char *file)
{
	DIR *dir;
	int i;

	i = 0;
	if (dirs && file && *dirs)
	{
		while (dirs[i])
		{
			dir = opendir(dirs[i]);
			if (find_file(dir, file))
			{
				closedir(dir);
				return (dirs[i]);
			}
			closedir(dir);
			++i;
		}
	}
	return (NULL);
}
