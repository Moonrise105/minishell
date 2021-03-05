/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:39:01 by olydden           #+#    #+#             */
/*   Updated: 2021/03/05 16:00:48 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

int		is_redirect(char c)
{
	char	*redirs;

	redirs = ";|><";
	if (ft_strchr(redirs, c))
		return (1);
	return (0);
}

int		is_quoter(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	set_quoter_flag(t_parser *p, char input)
{
	if (input == '\'')
	{
		if (p->q1)
			p->q1 = 0;
		else
			p->q1 = 1;
	}
	else
	{
		if (p->q2)
			p->q2 = 0;
		else
			p->q2 = 1;
	}
}

int		jmp_get(char c)
{
	char	*jmps;
	int		i;

	i = 0;
	jmps = ";|>]<";
	while (jmps[i])
	{
		if (c == jmps[i])
			return (i);
		++i;
	}
	return (-1);
}

void	parser_null(t_parser *p)
{
	p->first_arg = NULL;
	p->append_redir = 0;
	p->backslash = 0;
	p->args = NULL;
	p->commands = NULL;
	p->letters = NULL;
	p->q1 = 0;
	p->q2 = 0;
}
