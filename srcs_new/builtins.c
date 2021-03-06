/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:10:42 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 15:20:50 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

int		pwd(char **args)
{
	char dir[500];

	getcwd(dir, 500);
	ft_putstr(dir);
	ft_putstr("\n");
	g_status = 0;
	return (0);
}

int		my_exit(char **args)
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
				exit(255);
			}
			++i;
		}
		ft_putstr("exit\n");
		code = (args[0]) ? ft_atoi_orig(args[0]) : 0;
		exit(code);

	}
	ft_putstr("exit\n");
	exit(0);
	return (0);
}