/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00_arg_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:02:27 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 15:14:24 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

void	set_quoter_flags(int *q)
{
	if (*q)
		*q = 0;
	else
		*q = 1;
}

void	sign_question(char **number, char *val, t_list **lst)
{
	if (!ft_strcmp(val, "?"))
	{
		*number = ft_itoa(g_status);
		str_add(lst, *number);
		free(*number);
	}
}

void	sym_add(t_list **lst, char *sym)
{
	char *tmp;

	tmp = ft_strdup(sym);
	if (*lst)
		ft_lstadd_back(lst, ft_lstnew(tmp));
	else
		*lst = ft_lstnew(tmp);
}

void	str_add(t_list **lst, char *s)
{
	while (*s)
	{
		sym_add(lst, s);
		s++;
	}
}

void	add_str_or_sym(t_list **lst, t_pair **pair)
{
	if (*pair)
		str_add(lst, (*pair)->value);
	else
		sym_add(lst, "");
}
