/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 00:46:58 by olydden           #+#    #+#             */
/*   Updated: 2021/02/22 16:58:53 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;
	t_list *first;

	first = *lst;
	while (first)
	{
		tmp = first->next;
		if (del)
			del(first->content);
		free(first);
		first = tmp;
	}
	*lst = NULL;
}
