/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:54:56 by olydden           #+#    #+#             */
/*   Updated: 2021/03/05 15:55:31 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

void			lst_free(t_list **lst)
{
	if (lst && *lst)
		ft_lstclear(lst, free);
}

void			command_free(t_command **command)
{
	if (command && *command)
	{
		lst_free(&((*command)->args));
		free(*command);
		*command = NULL;
	}
}

void			commands_free(t_list **commands)
{
	t_list	*tmp;
	t_list	*first;

	if (commands && *commands)
	{
		first = *commands;
		while (first)
		{
			tmp = first->next;
			command_free((t_command **)(&(first->content)));
			free(first);
			first = tmp;
		}
		*commands = NULL;
	}
}
