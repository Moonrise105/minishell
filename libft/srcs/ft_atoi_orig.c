/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_orig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 20:07:25 by moonrise          #+#    #+#             */
/*   Updated: 2021/02/26 20:25:32 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_orig(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\r' || *str == '\v' || *str == '\f'))
		++str;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		++str;
	}
	return (result * sign);
}