/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:11:52 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 16:52:11 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char		**args_create(t_list *args)
{
	int		size;
	char	**argv;
	int		i;

	argv = NULL;
	if (args)
	{
		size = ft_lstsize(args);
		argv = (char**)malloc(sizeof(char*) * (size + 1));
		i = 0;
		while (args)
		{
			argv[i] = ft_strdup(args->content);
			args = args->next;
			++i;
		}
		argv[i] = NULL;
	}
	return (argv);
}

char		*split_path(char *s1, char *s2)
{
	char *tmp;
	char *res;

	tmp = ft_strjoin(s1, "/");
	res = ft_strjoin(tmp, s2);
	free(tmp);
	return (res);
}
