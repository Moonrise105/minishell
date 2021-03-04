/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 22:02:11 by olydden           #+#    #+#             */
/*   Updated: 2020/05/31 22:02:13 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*s;

	s = (unsigned char *)malloc(size * nmemb);
	if (!s)
		return (NULL);
	ft_bzero(s, (nmemb * size));
	return ((void *)s);
}
