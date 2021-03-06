/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:29:05 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 01:54:51 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

int		echo_flag(int *i, char **av)
{
	int		j;
	int		flag;

	flag = 1;
	while (av[*i] && !ft_strncmp(av[*i], "-n", 2))
	{
		j = 2;
		while (av[*i][j])
		{
			if (av[*i][j] != 'n')
			{
				flag = 0;
				break ;
			}
			++j;
		}
		if (!flag)
			break ;
		flag = 0;
		++(*i);
	}
	return (flag);
}

int		echo(char **av)
{
	int		n;
	int		i;
	int		j;

	i = 0;
	n = 1;
	if (av)
	{
		n = echo_flag(&i, av);
		while (av[i])
		{
			ft_putstr(av[i]);
			if (*(av[i]) && av[i + 1])
			{
				ft_putstr(" ");
			}
			++i;
		}
		if (n)
			ft_putstr("\n");
		g_status = 0;
	}
	return (0);
}
