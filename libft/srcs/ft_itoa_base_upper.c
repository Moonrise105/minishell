/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_upper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:10:48 by olydden           #+#    #+#             */
/*   Updated: 2020/08/10 14:03:07 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digits_counter(unsigned long long nb, int base)
{
	size_t		i;

	i = 0;
	while (nb)
	{
		nb /= base;
		i++;
	}
	return (i);
}

char			*ft_itoa_base_upper(unsigned long long value, int base)
{
	char	*result;
	char	*format;
	int		quantity;
	int		i;

	result = NULL;
	format = NULL;
	quantity = 0;
	i = 1;
	if (base < 2 || base > 16)
		return (NULL);
	if (value == 0)
		return (null_value(result));
	format = "0123456789ABCDEF";
	quantity = digits_counter(value, base);
	check_malloc(&result, quantity + 1);
	while (value != 0)
	{
		result[quantity - i++] = format[value % base];
		value /= base;
	}
	result[quantity] = '\0';
	return (result);
}
