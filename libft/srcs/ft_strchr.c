/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 17:40:03 by olydden           #+#    #+#             */
/*   Updated: 2020/08/04 18:51:28 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		i;
	char		*ss;

	i = 0;
	ss = (char *)s;
	while (i <= ft_strlen(s))
	{
		if (c == ss[i])
			return (&(ss[i]));
		i++;
	}
	return (NULL);
}
