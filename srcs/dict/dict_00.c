/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:37:28 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 16:59:39 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		pair_free(void *pair)
{
	if (pair)
	{
		free(((t_pair *)(pair))->key);
		free(((t_pair *)(pair))->value);
		free((t_pair *)pair);
	}
}

void		dict_free(t_list **dict)
{
	ft_lstclear(dict, pair_free);
}

void		free_array_char(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

t_pair		*dict_get(t_list *dict, char *key)
{
	t_pair *pair;

	pair = dict->content;
	while (ft_strcmp(pair->key, key) != 0)
	{
		dict = dict->next;
		if (dict)
			pair = dict->content;
		else
			return (NULL);
	}
	return (pair);
}

char		**split_f(char *s, char c)
{
	int		i;
	char	**p;

	p = NULL;
	if (s)
	{
		i = 0;
		p = (char**)malloc(sizeof(char*) * (2 + 1));
		p[2] = NULL;
		while (s[i] && s[i] != c)
			++i;
		p[0] = (char*)malloc(sizeof(char) * (i + 1));
		i = 0;
		while (s[i] && s[i] != c)
		{
			p[0][i] = s[i];
			++i;
		}
		p[0][i] = '\0';
		if (i == (int)ft_strlen(s))
			p[1] = ft_strdup("");
		else
			p[1] = ft_strdup(&s[++i]);
	}
	return (p);
}
