/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d5_d9_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 18:52:49 by olydden           #+#    #+#             */
/*   Updated: 2020/08/09 18:54:26 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	d9_specifier(t_flags *p_t_flags, int d)
{
	int	null;
	int spaces;
	int counter;
	int	printed;

	spaces = 0;
	counter = 0;
	printed = 0;
	null = p_t_flags->precision - ft_nbrlen(d);
	spaces = d10_specifier(null, p_t_flags, d);
	while (counter++ < null)
		printed += ft_putchar('0');
	if (p_t_flags->precision != 0 || d != 0)
	{
		ft_putnbr(d);
		printed += ft_nbrlen(d);
	}
	counter = 0;
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	return (printed);
}

int	d8_specifier(int null, t_flags *p_t_flags, int d)
{
	int	spaces;

	spaces = 0;
	if (p_t_flags->width && null > 0)
	{
		spaces = p_t_flags->width -
		p_t_flags->precision - 1;
	}
	else
		spaces = p_t_flags->width - ft_nbrlen(d);
	return (spaces);
}

int	d7_specifier(t_flags *p_t_flags, int d)
{
	int	printed;
	int	null;
	int spaces;
	int counter;

	printed = 0;
	spaces = 0;
	counter = 0;
	null = p_t_flags->precision - (ft_nbrlen(d) - 1);
	spaces = d8_specifier(null, p_t_flags, d);
	printed += ft_putchar('-');
	while (counter++ < null)
		printed += ft_putchar('0');
	if (d == -2147483648)
		printed += ft_putstr("2147483648");
	else
	{
		ft_putnbr(-d);
		printed += ft_nbrlen(-d);
	}
	counter = 0;
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	return (printed);
}

int	d6_specifier(int d, t_flags *p_t_flags)
{
	int printed;

	printed = 0;
	if (d < 0)
	{
		printed += d7_specifier(p_t_flags, d);
	}
	else
	{
		printed += d9_specifier(p_t_flags, d);
	}
	return (printed);
}

int	d5_specifier(t_flags *p_t_flags, int d, const char *format, int *i)
{
	int	printed;
	int	spaces;
	int	counter;

	printed = 0;
	spaces = 0;
	counter = 0;
	if (p_t_flags->precision >= 0)
		printed += d6_specifier(d, p_t_flags);
	else
	{
		if ((p_t_flags->width && d != 0) || (p_t_flags->width &&
				format[*i - 1] != '.'))
			spaces = p_t_flags->width - ft_nbrlen(d);
		else
			spaces = p_t_flags->width;
		if (format[*i - 1] != '.' || d != 0)
		{
			ft_putnbr(d);
			printed += ft_nbrlen(d);
		}
		while (counter++ < spaces)
			printed += ft_putchar(' ');
	}
	return (printed);
}
