/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d10_d14_specifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 18:58:27 by olydden           #+#    #+#             */
/*   Updated: 2020/08/09 19:00:05 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	d14_specifier(t_flags *p_t_flags, int d)
{
	int null;
	int counter;
	int printed;

	counter = 0;
	printed = 0;
	null = p_t_flags->precision - ft_nbrlen(d);
	printed += d15_specifier(p_t_flags, null, d);
	counter = 0;
	while (counter++ < null)
		printed += ft_putchar('0');
	if (p_t_flags->precision != 0 || d != 0)
	{
		ft_putnbr(d);
		printed += ft_nbrlen(d);
	}
	return (printed);
}

int	d13_specifier(t_flags *p_t_flags, int null, int d)
{
	int spaces;
	int	counter;
	int	printed;

	spaces = 0;
	counter = 0;
	printed = 0;
	if (p_t_flags->width && null > 0)
	{
		spaces = p_t_flags->width -
		p_t_flags->precision - 1;
	}
	else
		spaces = p_t_flags->width - ft_nbrlen(d);
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	printed += ft_putchar('-');
	return (printed);
}

int	d12_specifier(t_flags *p_t_flags, int d)
{
	int printed;
	int null;
	int counter;

	printed = 0;
	counter = 0;
	null = p_t_flags->precision - (ft_nbrlen(d) - 1);
	printed += d13_specifier(p_t_flags, null, d);
	while (counter++ < null)
		printed += ft_putchar('0');
	if (d == -2147483648)
	{
		ft_putnbr_u(2147483648);
		printed += ft_nbrlen_u(2147483648);
	}
	else
	{
		ft_putnbr(-d);
		printed += ft_nbrlen(-d);
	}
	return (printed);
}

int	d11_specifier(t_flags *p_t_flags, int d, const char *format, int *i)
{
	int printed;

	printed = 0;
	if (p_t_flags->precision >= 0)
	{
		if (d < 0)
		{
			printed += d12_specifier(p_t_flags, d);
		}
		else
		{
			printed += d14_specifier(p_t_flags, d);
		}
	}
	else
	{
		printed += d16_specifier(p_t_flags, format, i, d);
	}
	return (printed);
}

int	d10_specifier(int null, t_flags *p_t_flags, int d)
{
	int	spaces;

	spaces = 0;
	if ((p_t_flags->width && null > 0) ||
		(p_t_flags->precision == 0 &&
		null > 0) || d == 0)
		spaces = p_t_flags->width - p_t_flags->precision;
	else
		spaces = p_t_flags->width - ft_nbrlen(d);
	return (spaces);
}
