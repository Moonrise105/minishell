/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_u4_specifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 20:16:12 by olydden           #+#    #+#             */
/*   Updated: 2020/08/09 20:21:48 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	u4_specifier(t_flags *p_t_flags, unsigned int u)
{
	int printed;
	int null;
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
	while (counter++ < null)
		printed += ft_putchar('0');
	if (p_t_flags->precision != 0 || u != 0)
	{
		ft_putnbr_u(u);
		printed += ft_nbrlen_u(u);
	}
	counter = 0;
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	return (printed);
}

int	u3_specifier(t_flags *p_t_flags, unsigned int u, const char *format, int *i)
{
	int printed;

	printed = 0;
	if (p_t_flags->precision >= 0)
		printed += u4_specifier(p_t_flags, u);
	else
		printed += u5_specifier(p_t_flags, u, format, i);
	return (printed);
}

int	u2_specifier(t_flags *p_t_flags, unsigned int u, const char *format, int *i)
{
	int printed;

	printed = 0;
	if (p_t_flags->minus)
		printed += u3_specifier(p_t_flags, u, format, i);
	else
		printed += u7_specifier(p_t_flags, u, format, i);
	return (printed);
}

int	u1_specifier(t_flags *p_t_flags, unsigned int u)
{
	int printed;
	int null;
	int counter;

	printed = 0;
	null = 0;
	counter = 0;
	if (p_t_flags->width)
	{
		null = p_t_flags->width - ft_nbrlen_u(u);
		while (counter++ < null)
			printed += ft_putchar('0');
		ft_putnbr_u(u);
		printed += ft_nbrlen_u(u);
	}
	else
	{
		ft_putnbr_u(u);
		printed += ft_nbrlen_u(u);
	}
	return (printed);
}

int	u_specifier(t_flags *p_t_flags, va_list ap, const char *format, int *i)
{
	unsigned int	u;
	int				printed;

	u = va_arg(ap, unsigned int);
	printed = 0;
	if ((p_t_flags->null && p_t_flags->minus) ||
		(p_t_flags->null && (p_t_flags->precision >= 0)))
		p_t_flags->null = 0;
	if (p_t_flags->null)
		printed += u1_specifier(p_t_flags, u);
	else
		printed += u2_specifier(p_t_flags, u, format, i);
	return (printed);
}
