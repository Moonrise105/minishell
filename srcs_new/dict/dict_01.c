/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:38:04 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 16:27:36 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pair		*pair_get(char *s, char key)
{
	t_pair	*pair;
	char	**pair_split;

	if (s)
	{
		pair = (t_pair*)malloc(sizeof(t_pair));
		pair_split = split_f(s, key);
		if (pair_split)
		{
			pair->key = pair_split[0];
			pair->value = pair_split[1];
			free(pair_split);
		}
	}
	return (pair);
}

char		**dict_to_arr(t_list *dict)
{
	int		i;
	t_pair	*pair;
	char	**res;
	char	*tmp;

	res = (char**)malloc(sizeof(char*) * (ft_lstsize(dict) + 1));
	i = 0;
	while (dict)
	{
		pair = dict->content;
		tmp = ft_strjoin(pair->key, "=");
		res[i] = ft_strjoin(tmp, pair->value);
		free(tmp);
		dict = dict->next;
		++i;
	}
	res[i] = NULL;
	return (res);
}

t_list		*dict_create(char **array, char key)
{
	t_list	*dict;
	int		i;
	t_pair	*pair;

	dict = NULL;
	if (array && *array)
	{
		i = 0;
		pair = pair_get(array[i], key);
		dict = ft_lstnew(pair);
		++i;
		while (array[i])
		{
			ft_lstadd_back(&dict, ft_lstnew(pair_get(array[i], key)));
			++i;
		}
	}
	return (dict);
}

void		dict_delete_elem(t_list *dict, t_list *prev, char *key)
{
	t_pair	*pair;

	while (dict)
	{
		dict = dict->next;
		if (!dict)
			return ;
		pair = dict->content;
		if (ft_strcmp(pair->key, key) == 0)
		{
			prev->next = dict->next;
			pair_free(pair);
			free(dict);
			return ;
		}
		prev = dict;
	}
}

t_list		*dict_del(t_list *dict, char *key)
{
	t_pair		*pair;
	t_list		*prev;
	t_list		*first;

	first = dict;
	if (dict && key)
	{
		pair = dict->content;
		if (ft_strcmp(pair->key, key) == 0)
		{
			pair_free(pair);
			free(first);
			return (dict->next);
		}
		prev = dict;
		dict_delete_elem(dict, prev, key);
	}
	return (first);
}
