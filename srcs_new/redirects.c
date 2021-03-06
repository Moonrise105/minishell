/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:55:19 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/05 19:55:28 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

t_list		*find_left_redir(t_list *commands)
{
	t_command *command;

	command = commands->content;
	while (commands)
	{
		if (command->jmp_type != 1)
			break ;
		commands = commands->next;
		if (commands)
			command = commands->content;
	}
	if (commands)
	{
		if (command->jmp_type != 4)
			return (NULL);
	}
	return (commands);
}
