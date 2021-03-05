/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:52:37 by olydden           #+#    #+#             */
/*   Updated: 2021/03/05 17:25:20 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

int g_status;

void			print_errors(t_command *command, int prev)
{
	char	*c;

	if (command->jmp_type == 0 && prev == 0)
		c = ";;'\n";
	else if (command->jmp_type == 0 && prev != 0)
		c = ";'\n";
	else if (command->jmp_type == 1 && prev == 1)
		c = "||'\n";
	else if (command->jmp_type == 1 && prev != 1)
		c = "|'\n";
	else
		c = ">'\n";
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(c, 2);
}

int				check_jmp(t_command *command, int prev, t_list *commands)
{
	char		*jmps;

	jmps = "1234";
	if ((command->jmp_type == 0 || command->jmp_type == 1) && !command->args)
	{
		print_errors(command, prev);
		return (-1);
	}
	if ((ft_strchr(jmps, command->jmp_type + '0') && !commands->next) ||
			(ft_strchr(jmps, prev + '0') && !command->args))
	{
		ft_putstr_fd("minishell: syntax error near \
unexpected token `newline'\n", 2);
		return (-1);
	}
	return (0);
}

int				parser_check(t_list *commands)
{
	t_command	*command;
	int			prev;

	prev = 8;
	while (commands)
	{
		command = commands->content;
		if (check_jmp(command, prev, commands) < 0)
		{
			g_status = 2;
			return (-1);
		}
		else
			prev = command->jmp_type;
		commands = commands->next;
	}
	return (0);
}
