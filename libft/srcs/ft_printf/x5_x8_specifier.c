/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x5_x8_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 21:36:32 by olydden           #+#    #+#             */
/*   Updated: 2020/08/10 21:40:45 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		x8_specifier(t_flags *p_t_flags, char **pointer)
{
	int	printed;
	int	spaces;
	int	counter;
	int	null;

	printed = 0;
	spaces = 0;
	counter = 0;
	null = 0;
	if (x6_specifier(p_t_flags, pointer) < 0)
		return (-1);
	null = p_t_flags->precision - ft_strlen(*pointer);
	if (p_t_flags->width && null > 0)
		spaces = p_t_flags->width - p_t_flags->precision;
	else
		spaces = p_t_flags->width - ft_strlen(*pointer);
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	counter = 0;
	while (counter++ < null)
		printed += ft_putchar('0');
	if (p_t_flags->precision != 0 || **pointer != '0')
		printed += ft_putstr(*pointer);
	return (printed);
}

int		x7_specifier(t_flags *p_t_flags, char **pointer)
{
	int	printed;
	int	spaces;
	int	counter;

	printed = 0;
	spaces = 0;
	counter = 0;
	if (p_t_flags->precision >= 0)
	{
		if ((counter = x8_specifier(p_t_flags, pointer)) < 0)
			return (-1);
		printed += counter;
	}
	else
	{
		if (p_t_flags->width)
			spaces = p_t_flags->width - ft_strlen(*pointer);
		while (counter++ < spaces)
			printed += ft_putchar(' ');
		printed += ft_putstr(*pointer);
	}
	return (printed);
}

int		x6_specifier(t_flags *p_t_flags, char **pointer)
{
	if (p_t_flags->precision == 0 && **pointer == '0')
	{
		if (!(*pointer = ft_strdup("\0")))
			return (-1);
	}
	return (1);
}

int		x5_specifier(t_flags *p_t_flags, char **pointer)
{
	int	printed;
	int	spaces;
	int	counter;
	int	null;

	printed = 0;
	spaces = 0;
	counter = 0;
	null = 0;
	if (x6_specifier(p_t_flags, pointer) < 0)
		return (-1);
	null = p_t_flags->precision - ft_strlen(*pointer);
	if (p_t_flags->width && null > 0)
		spaces = p_t_flags->width - p_t_flags->precision;
	else
		spaces = p_t_flags->width - ft_strlen(*pointer);
	while (counter++ < null)
		printed += ft_putchar('0');
	printed += ft_putstr(*pointer);
	counter = 0;
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	return (printed);
}
