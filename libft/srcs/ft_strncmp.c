/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:14:04 by olydden           #+#    #+#             */
/*   Updated: 2020/05/28 13:26:22 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s21;

	i = 0;
	s11 = (unsigned char *)s1;
	s21 = (unsigned char *)s2;
	while (*s11 && *s21 && *s11 == *s21 && i < n)
	{
		s11++;
		s21++;
		i++;
	}
	if (i == n)
		return (0);
	return (*s11 - *s21);
}
