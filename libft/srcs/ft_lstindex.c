/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 22:24:33 by ctobias           #+#    #+#             */
/*   Updated: 2021/01/26 22:50:00 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstindex(t_list *lst, int ind)
{
	int i;

	i = 0;
	while (lst && i < ind)
	{
		lst = lst->next;
		++i;
	}
	return (lst);
}