/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 00:53:21 by olydden           #+#    #+#             */
/*   Updated: 2021/01/30 03:15:07 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	char	*dup_start;

	len = ft_strlen(s) + 1;
	if (!(dup = (char *)malloc(sizeof(char) * len)))
	{
		ft_free(dup);
		return (NULL);
	}
	dup_start = dup;
	while (*s)
		*dup++ = *s++;
	*dup = '\0';
	return (dup_start);
}
