/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 22:24:33 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 17:20:51 by olydden          ###   ########.fr       */
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
