/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:29:05 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/09 18:30:38 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_flag(char *str)
{
	int		i;

	if (ft_strncmp("-n", str, 2))
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		++i;
	}
	return (1);
}

int		echo_flag(int *i, char **av)
{
	int		flag;

	flag = 1;
	while (is_flag(av[*i]))
	{
		flag = 0;
		++(*i);
	}
	return (flag);
}

int		echo(char **av)
{
	int		n;
	int		i;

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
