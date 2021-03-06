/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:20:51 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 17:20:14 by olydden          ###   ########.fr       */
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
		return (NULL);
	dup_start = dup;
	while (n && *s)
	{
		*(dup++) = *(s++);
		n--;
	}
	*dup = '\0';
	return (dup_start);
}
