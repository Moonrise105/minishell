/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 13:27:00 by olydden           #+#    #+#             */
/*   Updated: 2020/05/28 15:53:35 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*bbig;
	size_t	little_len;
	size_t	j;
	size_t	i;

	bbig = (char *)big;
	little_len = ft_strlen(little);
	if (!little_len)
		return (bbig);
	if (ft_strlen(big) < little_len || len < little_len)
		return (NULL);
	i = 0;
	while (bbig[i] && i <= len - little_len)
	{
		j = 0;
		while (little[j] && little[j] == bbig[i + j])
			j++;
		if (j == little_len)
			return (&bbig[i]);
		i++;
	}
	return (NULL);
}
