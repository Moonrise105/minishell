/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:06:23 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/05 19:38:31 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

void		dict_set(t_list *dict, char *key, char *value)
{
	t_pair	*pair;

	if ((pair = dict_get(dict, key)))
	{
		free(pair->value);
		pair->value = ft_strdup(value);
	}
	else
	{
		pair = (t_pair*)malloc(sizeof(t_pair));
		pair->key = ft_strdup(key);
		pair->value = ft_strdup(value);
		ft_lstadd_back(&dict, ft_lstnew(pair));
	}
}

void		dict_print(t_list *dict, char delim)
{
	t_pair *pair;

	while (dict)
	{
		pair = dict->content;
		ft_putstr(pair->key);
		ft_putchar(delim);
		ft_putstr(pair->value);
		ft_putstr("\n");
		dict = dict->next;
	}
}
