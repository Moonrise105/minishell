/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:03:51 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 16:28:12 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		args_add(t_list **args, char *arg)
{
	if (*args)
		ft_lstadd_back(args, ft_lstnew(arg));
	else
		*args = ft_lstnew(arg);
}

void		args_add_after_redir(t_parser *p)
{
	if (p->first_arg && p->args)
	{
		args_add(&p->first_arg, word_get(&p->letters));
		lst_free(&p->letters);
	}
	else
	{
		args_add(&p->args, word_get(&p->letters));
		lst_free(&p->letters);
	}
}

t_command	*command_create(t_list *args, int jump)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	command->args = args;
	command->jmp_type = jump;
	return (command);
}

void		commands_add(t_list **commands, t_command *command)
{
	if (*commands)
		ft_lstadd_back(commands, ft_lstnew(command));
	else
		*commands = ft_lstnew(command);
}

void		check_redir_and_add(t_parser *p)
{
	if (!p->first_arg)
		p->first_arg = p->args;
	if (p->append_redir)
	{
		commands_add(&p->commands, command_create(p->args, 3));
		p->args = NULL;
		p->append_redir = 0;
	}
	else
		p->append_redir = 1;
}
