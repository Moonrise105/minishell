/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:19:54 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 15:11:32 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

t_list		*env_get(t_list **nw)
{
	static t_list	*env;

	if (nw)
		env = *nw;
	return (env);
}

int			env_f(char **av, int dec)
{
	int		i;
	char	**env;

	if (av)
	{
		env = dict_to_arr(env_get(NULL));
		i = 0;
		while (env[i])
		{
			if (dec)
				ft_putstr("declare -x ");
			ft_putstr(env[i]);
			ft_putstr("\n");
			++i;
		}
		free_array_char(env);
		return (0);
	}
	return (-1);
}

void		export_element(t_list *dict, char *arg)
{
	char **pair;
	char *tmp_s;

	pair = split_f(arg, '=');
	tmp_s = ft_strtrim(pair[1], " ");
	free(pair[1]);
	pair[1] = tmp_s;
	if (pair[1])
	{
		dict_set(dict, pair[0], pair[1]);
		free(pair[0]);
		free(pair[1]);
	}
	else
		free(pair[0]);
	free(pair);
}

int			export(char **av)
{
	t_list	*dict;
	int		i;

	if (!av[0])
	{
		env_f(av, 1);
		return (0);
	}
	dict = env_get(NULL);
	i = 0;
	while (av[i])
	{
		export_element(dict, av[i]);
		++i;
	}
	return (0);
}

int			unset(char **av)
{
	t_list	*dict;
	int		i;
	char	**env;

	i = 0;
	dict = env_get(NULL);
	while (av[i])
	{
		dict = dict_del(dict, av[i]);
		++i;
	}
	return (0);
}
