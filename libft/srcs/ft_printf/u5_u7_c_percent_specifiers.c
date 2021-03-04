/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u5_u7_c_percent_specifiers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:57:08 by olydden           #+#    #+#             */
/*   Updated: 2020/08/10 19:57:13 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	percent_specifier(t_flags *p_t_flags)
{
	int printed;
	int	spaces;
	int	counter;

	printed = 0;
	counter = 0;
	spaces = p_t_flags->width - 1;
	if (p_t_flags->minus)
	{
		printed += ft_putchar('%');
		while (counter++ < spaces)
			printed += ft_putchar(' ');
	}
	else
	{
		while (counter++ < spaces)
		{
			if (p_t_flags->null)
				printed += ft_putchar('0');
			else
				printed += ft_putchar(' ');
		}
		printed += ft_putchar('%');
	}
	return (printed);
}

int	c_specifier(t_flags *p_t_flags, va_list ap)
{
	int	printed;
	int spaces;
	int counter;

	printed = 0;
	spaces = 0;
	counter = 0;
	if (p_t_flags->width)
		spaces = p_t_flags->width - 1;
	if (p_t_flags->minus)
	{
		printed += ft_putchar(va_arg(ap, int));
		while (counter++ < spaces)
			printed += ft_putchar(' ');
	}
	else if (!p_t_flags->minus)
	{
		while (counter++ < spaces)
			printed += ft_putchar(' ');
		printed += ft_putchar(va_arg(ap, int));
	}
	else
		printed += ft_putchar(va_arg(ap, int));
	return (printed);
}

int	u7_specifier(t_flags *p_t_flags, unsigned int u, const char *format, int *i)
{
	int	printed;
	int spaces;
	int	counter;

	printed = 0;
	spaces = 0;
	counter = 0;
	if (p_t_flags->precision >= 0)
		printed += u6_specifier(p_t_flags, u);
	else
	{
		if (p_t_flags->width && format[*i - 1] != '.')
			spaces = p_t_flags->width - ft_nbrlen_u(u);
		else
			spaces = p_t_flags->width;
		while (counter++ < spaces)
			printed += ft_putchar(' ');
		if (format[*i - 1] != '.')
		{
			ft_putnbr_u(u);
			printed += ft_nbrlen_u(u);
		}
	}
	return (printed);
}

int	u6_specifier(t_flags *p_t_flags, unsigned int u)
{
	int	printed;
	int	null;
	int spaces;
	int counter;

	printed = 0;
	spaces = 0;
	counter = 0;
	null = p_t_flags->precision - ft_nbrlen_u(u);
	if ((p_t_flags->width && null > 0) ||
		(p_t_flags->precision == 0 && null > 0) || u == 0)
		spaces = p_t_flags->width - p_t_flags->precision;
	else
		spaces = p_t_flags->width - ft_nbrlen_u(u);
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	counter = 0;
	while (counter++ < null)
		printed += ft_putchar('0');
	if (p_t_flags->precision != 0 || u != 0)
	{
		ft_putnbr_u(u);
		printed += ft_nbrlen_u(u);
	}
	return (printed);
}

int	u5_specifier(t_flags *p_t_flags, unsigned int u, const char *format, int *i)
{
	int	printed;
	int spaces;
	int counter;

	printed = 0;
	spaces = 0;
	counter = 0;
	if ((p_t_flags->width && u != 0) || (p_t_flags->width &&
				format[*i - 1] != '.'))
		spaces = p_t_flags->width - ft_nbrlen_u(u);
	else
		spaces = p_t_flags->width;
	if (p_t_flags->precision != 0 && format[*i - 1] != '.')
	{
		ft_putnbr_u(u);
		printed += ft_nbrlen_u(u);
	}
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	return (printed);
}
