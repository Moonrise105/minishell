/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:55:19 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 16:30:31 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
