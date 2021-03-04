/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:20:51 by olydden           #+#    #+#             */
/*   Updated: 2021/02/22 17:13:04 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	char	*dup_start;

	if (n < 0)
		return ((char *)s);
	if (!(dup = (char *)malloc(sizeof(char) * (n + 1))))
	{
		//ft_free(dup);
		return (NULL);
	}
	dup_start = dup;
	while (n && *s)
	{
		*(dup++) = *(s++);
		n--;
	}
	*dup = '\0';
	return (dup_start);
}
