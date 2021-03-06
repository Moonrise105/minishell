/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:14:04 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 17:18:41 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_end(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s21;
	int				len1;
	int				len2;
	size_t			i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	s11 = (unsigned char *)s1;
	s21 = (unsigned char *)s2;
	while (s11[len1 - 1] && s21[len2 - 1] && s11[len1 - 1]
			== s21[len2 - 1] && i < n)
	{
		i++;
		len1--;
		len2--;
	}
	if (i == n)
		return (0);
	return (*s11 - *s21);
}
