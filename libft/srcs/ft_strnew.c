/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:52:38 by olydden           #+#    #+#             */
/*   Updated: 2021/01/23 21:51:52 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(int size)
{
	char	*str;

	str = NULL;
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (size && str[size])
	{
		str[size] = '\0';
		size--;
	}
	return (str);
}
