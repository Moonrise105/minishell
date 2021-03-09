/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:56:25 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/09 18:43:41 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		manager(t_list *commands)
{
	t_command	*command;
	int			code;

	while (commands)
	{
		signal(SIGINT, SIG_DFL);
		command = commands->content;
		parse_args(command->args);
		if (command->jmp_type == 0 || command->jmp_type == -1)
			code = semicolon_handler(command);
		else if (command->jmp_type == 1)
		{
			if (find_left_redir(commands))
				commands = left_redir_handler(find_left_redir(commands));
			else
				commands = pipe_handler(commands);
		}
		else if (command->jmp_type == 2 || command->jmp_type == 3)
			commands = right_redir_handler(commands, NULL, 0);
		else if (command->jmp_type == 4)
			commands = left_redir_handler(commands);
		commands = commands->next;
	}
	return (code);
}
