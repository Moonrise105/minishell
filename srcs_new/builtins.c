/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:10:42 by ctobias           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/06 16:58:33 by ctobias          ###   ########.fr       */
=======
/*   Updated: 2021/03/06 16:58:28 by olydden          ###   ########.fr       */
>>>>>>> 53eea8371c6f19586f44b5b97ee56206c0c535c1
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pwd(char **args)
{
	char dir[500];

	getcwd(dir, 500);
	ft_putstr(dir);
	ft_putstr("\n");
	g_status = 0;
	return (0);
}

int		print_error(void)
{
	ft_putstr("exit\n");
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (127);
}

void	print_str_errors(char *c)
{
	ft_putstr("exit\n");
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int		my_exit(char **args)
{
	int		i;
	int		code;
	char	*c;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			if (i > 0)
				return (print_error());
			if (!is_numeric(args[i]))
			{
				print_str_errors(args[i]);
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
