/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 23:43:40 by olydden           #+#    #+#             */
/*   Updated: 2020/05/28 23:53:13 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	cc;
	unsigned char	*d;
	unsigned char	*s;

	cc = (unsigned char)c;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n--)
	{
		*d++ = *s++;
		if (*(d - 1) == cc)
			return (d);
	}
	return (0);
}
