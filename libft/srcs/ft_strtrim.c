/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:52:59 by olydden           #+#    #+#             */
/*   Updated: 2020/05/31 17:53:48 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len_s1;
	char		*newstr;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len_s1 = ft_strlen(s1);
	while (len_s1 && ft_strchr(set, s1[len_s1]))
		len_s1--;
	newstr = ft_substr((char *)s1, 0, len_s1 + 1);
	return (newstr);
}
