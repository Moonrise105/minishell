/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d15_d16_p_specifiers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 19:03:38 by olydden           #+#    #+#             */
/*   Updated: 2020/08/10 21:39:26 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	d16_specifier(t_flags *p_t_flags, const char *format, int *i, int d)
{
	int printed;
	int spaces;
	int counter;

	printed = 0;
	spaces = 0;
	counter = 0;
	if ((p_t_flags->width && d != 0) || (p_t_flags->width &&
				format[*i - 1] != '.'))
		spaces = p_t_flags->width - ft_nbrlen(d);
	else
		spaces = p_t_flags->width;
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	if (format[*i - 1] != '.' || d != 0)
	{
		ft_putnbr(d);
		printed += ft_nbrlen(d);
	}
	return (printed);
}

int	d15_specifier(t_flags *p_t_flags, int null, int d)
{
	int printed;
	int	spaces;
	int counter;

	printed = 0;
	spaces = 0;
	counter = 0;
	if ((p_t_flags->width && null > 0) ||
		(p_t_flags->precision == 0 &&
		null > 0) || d == 0)
		spaces = p_t_flags->width - p_t_flags->precision;
	else
		spaces = p_t_flags->width - ft_nbrlen(d);
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	return (printed);
}
