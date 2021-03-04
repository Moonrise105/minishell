/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_d4_specifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 18:47:49 by olydden           #+#    #+#             */
/*   Updated: 2020/08/10 07:47:01 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	d4_specifier(t_flags *p_t_flags, const char *format, int *i, int d)
{
	int printed;

	printed = 0;
	if (p_t_flags->minus)
	{
		printed += d5_specifier(p_t_flags, d, format, i);
	}
	else
	{
		printed += d11_specifier(p_t_flags, d, format, i);
	}
	return (printed);
}

int	d3_specifier(int d)
{
	int	printed;

	printed = 0;
	if (d == -2147483648)
		printed += ft_putstr("2147483648");
	else
	{
		ft_putnbr(-d);
		printed += ft_nbrlen(-d);
	}
	return (printed);
}

int	d2_specifier(int d, int null)
{
	int	printed;
	int counter;

	printed = 0;
	counter = 0;
	if (d < 0)
	{
		printed += ft_putchar('-');
		while (counter++ < null)
			printed += ft_putchar('0');
		printed += d3_specifier(d);
	}
	else
	{
		while (counter++ < null)
			printed += ft_putchar('0');
		ft_putnbr(d);
		printed += ft_nbrlen(d);
	}
	return (printed);
}

int	d1_specifier(t_flags *p_t_flags, const char *format, int *i, int d)
{
	int	printed;
	int null;

	printed = 0;
	null = 0;
	if (p_t_flags->width)
	{
		null = p_t_flags->width - ft_nbrlen(d);
		printed += d2_specifier(d, null);
	}
	else
	{
		if ((d != 0 && format[*i - 1] == '.') ||
			(d == 0 && format[*i - 1] != '.')
			|| (d != 0 && format[*i - 1] != '.'))
		{
			ft_putnbr(d);
			printed += ft_nbrlen(d);
		}
	}
	return (printed);
}

int	d_specifier(t_flags *p_t_flags, va_list ap, const char *format, int *i)
{
	int	printed;
	int d;

	printed = 0;
	d = 0;
	if ((p_t_flags->null && p_t_flags->minus) ||
		(p_t_flags->null && (p_t_flags->precision >= 0)))
		p_t_flags->null = 0;
	d = va_arg(ap, int);
	if (p_t_flags->null)
	{
		printed += d1_specifier(p_t_flags, format, i, d);
	}
	else
	{
		printed += d4_specifier(p_t_flags, format, i, d);
	}
	return (printed);
}
