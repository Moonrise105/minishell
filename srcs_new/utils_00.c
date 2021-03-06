/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:11:52 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 15:12:03 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

t_list		*skip_jmps(t_list *commands, char *jmps)
{
	t_command	*command;

	command = commands->content;
	while (commands && ft_strchr(jmps, command->jmp_type + '0'))
	{
		commands = commands->next;
		command = commands->content;
	}
	return (commands);
}

int			is_numeric(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (0);
		++i;
	}
	return (1);
}
