/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_x4_specifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 21:30:43 by olydden           #+#    #+#             */
/*   Updated: 2020/08/10 13:53:20 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	x4_specifier(t_flags *p_t_flags, char **pointer)
{
	int	printed;
	int	spaces;
	int	counter;

	printed = 0;
	spaces = 0;
	counter = 0;
	if (p_t_flags->precision >= 0)
	{
		if ((counter = x5_specifier(p_t_flags, pointer)) < 0)
			return (-1);
		printed += counter;
	}
	else
	{
		if (p_t_flags->width)
			spaces = p_t_flags->width - ft_strlen(*pointer);
		printed += ft_putstr(*pointer);
		while (counter++ < spaces)
			printed += ft_putchar(' ');
	}
	return (printed);
}

int	x3_specifier(t_flags *p_t_flags, char **pointer)
{
	int printed;
	int	null;
	int counter;

	printed = 0;
	null = 0;
	counter = 0;
	if (p_t_flags->width)
	{
		null = p_t_flags->width - ft_strlen(*pointer);
		while (counter++ < null)
			printed += ft_putchar('0');
		printed += ft_putstr(*pointer);
	}
	else
		printed += ft_putstr(*pointer);
	return (printed);
}

int	x2_specifier(t_flags *p_t_flags, char **pointer)
{
	int printed;
	int j;

	printed = 0;
	j = 0;
	if (p_t_flags->null)
		printed += x3_specifier(p_t_flags, pointer);
	else
	{
		if (p_t_flags->minus)
		{
			if ((j = x4_specifier(p_t_flags, pointer)) < 0)
				return (-1);
			printed += j;
		}
		else
		{
			if ((j = x7_specifier(p_t_flags, pointer)) < 0)
				return (-1);
			printed += j;
		}
	}
	return (printed);
}

int	x1_specifier(const char *format, int *i, char **pointer, unsigned int u)
{
	if (format[*i - 1] == '.')
	{
		if (!(*pointer = ft_strdup("")))
			return (-1);
	}
	else
	{
		if (format[*i] == 'x')
		{
			if (!(*pointer = ft_itoa_base(u, 16)))
				return (-1);
		}
		else
		{
			if (!(*pointer = ft_itoa_base_upper(u, 16)))
				return (-1);
		}
	}
	return (1);
}

int	x_specifier(t_flags *p_t_flags, va_list ap, const char *format, int *i)
{
	unsigned int	u;
	char			*pointer;
	int				printed;
	int				j;

	u = va_arg(ap, int);
	pointer = NULL;
	printed = 0;
	j = 0;
	if ((p_t_flags->null && p_t_flags->minus) || (p_t_flags->null &&
			(p_t_flags->precision >= 0)))
		p_t_flags->null = 0;
	if (x1_specifier(format, i, &pointer, u) < 0)
	{
		ft_free(pointer);
		return (-1);
	}
	if ((j = x2_specifier(p_t_flags, &pointer)) < 0)
		return (-1);
	printed += j;
	ft_free(pointer);
	return (printed);
}
