/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:14:04 by olydden           #+#    #+#             */
/*   Updated: 2021/02/25 20:46:24 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h> // delete

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s11;
	unsigned char	*s21;

	s11 = (unsigned char *)s1;
	s21 = (unsigned char *)s2;
	while (*s11 && *s21 && *s11 == *s21)
	{
		s11++;
		s21++;
	}
	// if (*s21 == '\0')
	// 	return (0);
	// printf("line = %s\nid = %s", s11, s21);
	return (*s11 - *s21);
}
