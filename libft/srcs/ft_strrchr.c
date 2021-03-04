/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 15:58:08 by olydden           #+#    #+#             */
/*   Updated: 2020/05/28 17:39:02 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	*ss;

	i = 0;
	len = ft_strlen(s);
	ss = (char *)s;
	while (i <= len)
	{
		if (c == ss[len - i])
			return (&(ss[len - i]));
		i++;
	}
	return (0);
}
